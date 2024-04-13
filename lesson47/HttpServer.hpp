#pragma once

#include <iostream>
#include <string>
#include <pthread.h>
#include "Socket.hpp"

static const int defaultport = 8080;

class ThreadData
{
public:
    int _sockfd;
};

class HttpServer
{
public:
    HttpServer(uint16_t port = defaultport) : _port(port)
    {
    }

    bool Start()
    {
        _listensock.Socket();
        _listensock.Bind(_port);
        _listensock.Listen();

        for (;;)
        {
            std::string clientip;
            uint16_t clientport;
            int sockfd = _listensock.Accept(&clientip, &clientport);
            pthread_t tid;
            ThreadData *td = new ThreadData();
            td->_sockfd = sockfd;
            pthread_create(&tid, nullptr, ThreadRun, td);
        }
    }

    static void *ThreadRun(void *args)
    {
        pthread_detach(pthread_self());
        ThreadData *td = static_cast<ThreadData *>(args);
        char buffer[10240];
        ssize_t n = recv(td->_sockfd, buffer, sizeof(buffer) - 1, 0);
        if (n > 0)
        {
            buffer[n] = 0;
            std::cout << buffer;
        }
    }

    ~HttpServer() {}

private:
    Sock _listensock;
    uint16_t _port;
};