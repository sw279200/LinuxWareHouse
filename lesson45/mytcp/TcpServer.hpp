#pragma once

#include<iostream>
#include "Log.hpp"
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include"ThreadPool.hpp"
#include<string>
#include<string.h>

const std::string defaultip = "0.0.0.0";
const int backlog = 5;

enum{
    SocketError = 1,
    BindError,
    ListenError,


};

class TcpServer
{
public:
    TcpServer(const uint16_t & port,const std::string & ip = defaultip)
    :_port(port),_ip(ip),_listensock(-1)
    {}

    void Init()
    {
        //创建套接字
        _listensock = socket(AF_INET,SOCK_STREAM,0);
        if(_listensock<0)
        {
            log.LogMessage(FATAL,"create socket error, errno: %d, strerror:%s",errno,strerror(errno));
            exit(SocketError);
        }
        log.LogMessage(INFO,"create socket success,_listensock:%d ",_listensock);

        struct sockaddr_in local;
        memset(&local,0,sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        inet_pton(AF_INET,_ip.c_str(),&(local.sin_addr));

        if(bind(_listensock,(struct sockaddr*)&local,sizeof(local))<0)
        {
            log.LogMessage(FATAL,"bind error, errno: %d, strerror:%s",errno,strerror(errno));
            exit(BindError);
        }
        log.LogMessage(INFO,"bind success,_listensock:%d ",_listensock);

        
        if(listen(_listensock,backlog)<0)
        {
            log.LogMessage(FATAL,"listen error, errno: %d, strerror:%s",errno,strerror(errno));
            exit(ListenError);
        }
        log.LogMessage(INFO,"listen success,_listensock:%d ",_listensock);

    }

    void StartServer()
    {
        log.LogMessage(INFO,"TcpServer is running ...");
        while(true)
        {
            char buffer[4096];
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            int sockfd = accept(_listensock,(struct sockaddr*)&client,&len);
            if(sockfd<0)
            {
                log.LogMessage(WARNING,"accept error, errno: %d, strerror:%s",errno,strerror(errno));
                continue;
            }

            char clientip[32];
            inet_ntop(AF_INET,&(client.sin_addr),clientip,sizeof(clientip));
            uint16_t clientport = ntohs(client.sin_port);

            log.LogMessage(INFO,"get a new line ... client ip: %s",clientip);

            Server(sockfd,clientip,clientport);
        }
    }

    void Server(const int& fd,const std::string& clientip,const uint16_t & clientport)
    {
        char buffer[4096];
        while(true)
        {
            ssize_t n = read(fd,buffer,sizeof(buffer));
            if(n>0)
            {
                buffer[n] = 0;
                std::cout<<"client say# "<<buffer<<std::endl;
                std::string echo_string = "server echo# ";
                echo_string+=buffer;
                write(fd,echo_string.c_str(),echo_string.size());
            }
            else if(n==0)
            {
                log.LogMessage(INFO, "%s:%d quit,server close sockfd:%d", clientip.c_str(), clientport, fd);
                break;
            }
            else 
            {
                 log.LogMessage(WARNING, "read error,sockfd:%d,clientip:%s ,clientport:%d ", fd, clientip.c_str(), clientport);
                 break;
            }
        }
    }

    ~TcpServer(){}

private:
    int _listensock;
    uint16_t _port;
    std::string _ip;
};
