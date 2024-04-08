#pragma once
#include"Log.hpp"
#include"Socket.hpp"
#include<signal.h>

class TcpServer
{
public:
    TcpServer(){}

    bool ServerInit()
    {
        _listensock.Socket();
        _listensock.Bind(_port);
        _listensock.Listen();
        return true;
    }

    void Start()
    {
        signal(SIGCHLD,SIG_IGN);
        while(true)
        {
            std::string serverip;
            uint16_t serverport;
            int sockfd = _listensock.Accept(&serverip,&serverport);
            if(sockfd<0)
            {
                continue;
            }

            //提供服务
            if(fork() == 0)
            {
                _listensock.Close();
                //数据计算

                exit(0);
            }

            close(sockfd);
        }
    }

    ~TcpServer(){}
private:
    uint16_t _port;
    Sock _listensock;
};