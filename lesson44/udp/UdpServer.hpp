#pragma once
#include "Log.hpp"
#include <string>
#include <strings.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<errno.h>

const uint16_t defaultport = 8080;
const std::string defaultip = "0.0.0.0";
const int size = 1024;

enum
{
    SOCKET_ERR = 1,
    BIND_ERR

};

class UdpServer
{
public:
    UdpServer(const uint16_t &port = defaultport, const std::string &ip = defaultip)
        :_sockfd(0), _port(port), _ip(ip),_isrunning(false)
    {
    }
    void Init()
    {
        //1.创建udp socket
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            log.LogMessage(FATAL, "socket create error,_sockfd: %d", _sockfd);
            exit(SOCKET_ERR);
        }
        log.LogMessage(INFO, "socket create success, _sockfd: %d ", _sockfd);

        //2.bind socket
        struct sockaddr_in local;
        bzero(&local,sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);//需要保证我的端口号是网络字节序列，因为该端口号是要给对方发送的。
        local.sin_addr.s_addr = inet_addr(_ip.c_str()); //1.string->uint32_t 2.uint32_t 必须是网络序列的
        //local.sin_addr.s_addr = htonl(INADDR_ANY);

        int n = bind(_sockfd,(const struct sockaddr *)&local,sizeof(local));
        if(n<0)
        {
            log.LogMessage(FATAL,"bind error , error: %d, error string : %s",errno,strerror(errno));
            exit(BIND_ERR);
        }
            log.LogMessage(INFO,"bind success , error: %d, error string : %s",errno,strerror(errno));

    }

    void Run()
    {
        _isrunning = true;
        char inbuffer[size];
        while(_isrunning)
        {
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            ssize_t n = recvfrom(_sockfd,inbuffer,sizeof(inbuffer)-1,0,(struct sockaddr *)&client,&len);
            if(n<0)
            {
                log.LogMessage(WARNING,"recvfrom error, errno: %d ,errno string : %s",errno,strerror(errno));
                continue;
            }
            inbuffer[n] = 0;
            std::cout<<"issending"<<std::endl;
            //充当了一次数据的处理
            std::string info = inbuffer;
            std::string echo_string = "sever echo# "+info;

            sendto(_sockfd,echo_string.c_str(),echo_string.size(),0,(const sockaddr*)&client,len);

        }
    }

    ~UdpServer() 
    {
        if(_sockfd>0) close(_sockfd);
    }

private:
    uint16_t _port;//服务器进程的端口号
    std::string _ip;//字符串类型ip地址
    int _sockfd;//网络文件描述符
    bool _isrunning;
};