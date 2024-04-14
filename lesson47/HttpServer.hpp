#pragma once

#include <iostream>
#include <string>
#include <pthread.h>
#include "Socket.hpp"

static const int defaultport = 8080;

class ThreadData
{
public:
    ThreadData(int fd) : _sockfd(fd)
    {
    }

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
            if(sockfd<0) continue;
            log.LogMessage(INFO,"get a new line, sockfd: %d ",sockfd);
            pthread_t tid;
            ThreadData *td = new ThreadData(sockfd);
            pthread_create(&tid, nullptr, ThreadRun, td);
        }
    }

    static void HandlerHttp(int sockfd)
    {
        char buffer[10240];
        ssize_t n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (n > 0)
        {
            buffer[n] = 0;
            std::cout << buffer;
            // 返回响应的过程
            std::string text = "hello world";
            std::string response_line = "HTTP/1.0 200 OK\r\n";
            std::string response_header = "Content-Length: ";
            response_header += std::to_string(text.size());
            response_header += "\r\n";
            std::string blank_line = "\r\n";

            std::string response = response_line;
            response += response_header;
            response += blank_line;
            response += text;

            send(sockfd, response.c_str(), response.size(), 0);
        }
         close(sockfd);
    }

    static void *ThreadRun(void *args)
    {
        pthread_detach(pthread_self());
        ThreadData *td = static_cast<ThreadData *>(args);
        HandlerHttp(td->_sockfd);
        delete td;
        return nullptr;
    }

    ~HttpServer() {}

private:
    Sock _listensock;
    uint16_t _port;
};