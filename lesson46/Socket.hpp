#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "Log.hpp"
#include <cstring>

enum
{
    SocketErr = 2,
    BindErr,
    ListenErr,
};

const int backlog = 10;

class Sock
{
public:
    Sock() {}
    ~Sock() {}

public:
    void Socket()
    {
        _sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (_sockfd < 0)
        {
            log.LogMessage(FATAL, "socket error , %s : %d", strerror(errno), errno);
            exit(SocketErr);
        }
    }

    void Bind(uint16_t port)
    {
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;

        if(bind(_sockfd,(struct sockaddr*)&local,sizeof(local))<0)
        {
            log.LogMessage(FATAL, "bind error , %s : %d", strerror(errno), errno);
            exit(BindErr);
        }
    }

    void Listen()
    {
        if(listen(_sockfd,backlog)<0)
        {
            log.LogMessage(FATAL, "listen error , %s : %d", strerror(errno), errno);
            exit(ListenErr);
        }
    }

    int Accept(std::string *clientip,uint16_t * clientport)
    {   
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int newfd = accept(_sockfd,(struct sockaddr*)&peer,&len);
        if(newfd<0)
        {
            log.LogMessage(WARNING,"accep error, %s : %d",strerror(errno),errno);
            return -1;
        }
        *clientport = ntohs(peer.sin_port);
        char ipstr[64];
        inet_ntop(AF_INET,&(peer.sin_addr),ipstr,sizeof(ipstr));
        *clientip = ipstr;

        return newfd;
    }

    int Connect(const std::string & clientip,const uint16_t & clientport)
    {
        struct sockaddr_in peer;
        memset(&peer,0,sizeof(peer));
        peer.sin_family = AF_INET;
        peer.sin_port = htons(clientport);
        inet_pton(AF_INET,clientip.c_str(),&(peer.sin_addr));
        int n = connect(_sockfd,(struct sockaddr*)&peer,sizeof(peer));
        if(n<0)
        {
            std::cerr<<"connect to error ..."<<std::endl;
            return false;
        }

        return true;
    }

    int GetFd()
    {
        return _sockfd;
    }

    void Close()
    {
        close(_sockfd);
    }

private:
    int _sockfd;
};