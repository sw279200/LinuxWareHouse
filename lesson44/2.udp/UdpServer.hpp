#pragma once
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"
#include <errno.h>
#include <cstring>

const std::string defaultip = "0.0.0.0";
const uint16_t defaultport = 8080;
const int size = 1024;

enum
{
    Socket_Error = 1,
    Bind_Error,

};

class UdpServer
{
public:
    UdpServer(const uint16_t &port = defaultport, const std::string &ip = defaultip)
        : _ip(ip), _port(port)
    {
    }

    void Init()
    {
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            log.LogMessage(FATAL, "create socket error, errno:%d , error string: %s", errno, strerror(errno));
            exit(Socket_Error);
        }
        log.LogMessage(INFO, "create socket success, errno:%d , error string: %s", errno, strerror(errno));

        struct sockaddr_in local;
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_addr.s_addr = inet_addr(_ip.c_str());
        local.sin_port = htons(_port);
        socklen_t len = sizeof(local);
        // bind
        if (bind(_sockfd, (struct sockaddr *)&local, len) < 0)
        {
            log.LogMessage(FATAL, "bind error, errno:%d , error string: %s", errno, strerror(errno));
            exit(Bind_Error);
        }
        log.LogMessage(INFO, "bind success, errno:%d , error string: %s", errno, strerror(errno));
    }

    void Run()
    {
        log.LogMessage(INFO, "server is running ...");
        char buffer[size];
        
        while (true)
        {
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            log.LogMessage(INFO, "server is recever from client:");
            ssize_t n = recvfrom(_sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client, &len);
            if (n < 0)
            {
                log.LogMessage(WARNING, "recvfrom error");
                continue;
            }
            log.LogMessage(INFO, "client say# %s", buffer);
            buffer[n] = 0;

            //相当于一次数据处理
            std::string info = "server say# ";
            info += buffer;
            sendto(_sockfd, info.c_str(), info.size(), 0, (struct sockaddr *)&client, len);
        }
    }

    ~UdpServer() {}

private:
    int _sockfd;     // 套接字文件描述符
    std::string _ip; // 服务端ip地址
    uint16_t _port;  // 服务器端口号
};