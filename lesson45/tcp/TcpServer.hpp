#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "Log.hpp"
#include <cstring>
#include<pthread.h>
#include"ThreadPool.hpp"
#include "task.hpp"
#include<signal.h>
#include"Daemon.hpp"

const int defaultfd = -1;
const std::string defaultip = "0.0.0.0";
const int backlog = 5;

enum
{
    UsageError = 1,
    SocketError,
    BindError,
    ListenError,
};

class TcpServer;

class ThreadData1
{
public:
    ThreadData1(int fd,const std::string & ip,const uint16_t & port,TcpServer* t)
    :sockfd(fd),clientip(ip),clientport(port),tsvr(t)
    {

    }

public:
    int sockfd;
    std::string clientip;
    uint16_t clientport;
    TcpServer* tsvr;
};

class TcpServer
{

public:
    TcpServer(const uint16_t port, const std::string &ip = defaultip)
        : _listensock(-1), _port(port), _ip(ip)
    {
    }

    void InitServer()
    {
        _listensock = socket(AF_INET, SOCK_STREAM, 0);
        if (_listensock < 0)
        {
            log.LogMessage(FATAL, "create socket error , errno:%d, strerror: %s", errno, strerror(errno));
            exit(SocketError);
        }
        log.LogMessage(INFO, "create socket success ,_listensock:%d", _listensock);

        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        inet_aton(_ip.c_str(), &(local.sin_addr));

        if (bind(_listensock, (struct sockaddr *)&local, sizeof(local)) < 0)
        {
            log.LogMessage(FATAL, "bind error , errno:%d, strerror: %s", errno, strerror(errno));
            exit(BindError);
        }
        log.LogMessage(INFO, "bind socket success ,_listensock:%d", _listensock);

        // Tcp是面向连接的，所以服务器一般是比较“被动”的,服务器一种处于一种
        if (listen(_listensock, backlog) < 0)
        {
            log.LogMessage(FATAL, "listen error , errno:%d, strerror: %s", errno, strerror(errno));
            exit(ListenError);
        }
        log.LogMessage(INFO, "listen success ,_listensock:%d", _listensock);
    }

    // static void* Routine(void * args)
    // {
    //     pthread_detach(pthread_self());
    //     ThreadData* td = static_cast<ThreadData*>(args);
    //     td->tsvr->Server(td->sockfd,td->clientport,td->clientip);
    //     delete td;
    //     return nullptr;
    // }

    void Start()
    {
        Daemon();
        ThreadPool<Task>::GetInstance()->Start();
        log.LogMessage(INFO, "tcpServer is running ...");
        for (;;)
        {
            // 1.获取新链接
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            int sockfd = accept(_listensock, (struct sockaddr *)&client, &len);
            if (sockfd < 0)
            {
                log.LogMessage(WARNING, "accept error , errno:%d, strerror: %s", errno, strerror(errno));
                continue;
            }
            uint16_t clientport = ntohs(client.sin_port);
            char clientip[32];
            inet_ntop(AF_INET, &(client.sin_addr), clientip, sizeof(clientip));

            // 2.根据新连接来进行通信
            log.LogMessage(INFO, "get a new link ... client ip : %s, client port : %d , sockfd:%d", clientip, clientport, sockfd);

            // version 1 --单进程版
            //  Server(sockfd,clientport,clientip);
            //  close(sockfd);

            // // version2 --多进程版
            // pid_t id = fork();
            // if (id == 0)
            // {
            //     // child
            //     close(_listensock);
            //     if(fork()>0)
            //     {
            //         exit(0);
            //     }
            //     Server(sockfd, clientport, clientip);//孙子进程
            //     close(sockfd);
            //     exit(0);
            // }
            // close(sockfd);
            // //father
            // pid_t rid = waitpid(id,nullptr,0);
            // (void)rid;

            // ThreadData * td = new ThreadData(sockfd,clientip,clientport,this);

            // //version3 --多线程版本
            // pthread_t tid;
            // pthread_create(&tid,nullptr,Routine,td);

            //version4 线程池版本
            Task t(sockfd,clientport,clientip);
            ThreadPool<Task>::GetInstance()->Push(t);
        }
    }

    // void Server(int sockfd, const uint16_t &clientport, const std::string &clientip)
    // {
    //     char buffer[4096];
    //     // 测试代码
    //     while (true)
    //     {
    //         ssize_t n = read(sockfd, buffer, sizeof(buffer));
    //         if (n > 0)
    //         {
    //             buffer[n] = 0;
    //             std::cout << "client say# " << buffer << std::endl;
    //             std::string echo_string = "tcpserver echo# ";
    //             echo_string += buffer;

    //             write(sockfd, echo_string.c_str(), echo_string.size());
    //         }
    //         else if (n == 0)
    //         {
    //             log.LogMessage(INFO, "%s:%d quit,server close sockfd:%d", clientip.c_str(), clientport, sockfd);
    //             break;
    //         }
    //         else
    //         {
    //             log.LogMessage(WARNING, "read error,sockfd:%d,clientip:%s ,clientport:%d ", sockfd, clientip.c_str(), clientport);
    //             break;
    //         }
    //     }
    // }
    ~TcpServer() {}

private:
    int _listensock;
    uint16_t _port;
    std::string _ip;
};