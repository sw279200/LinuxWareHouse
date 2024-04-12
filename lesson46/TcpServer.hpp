#pragma once
#include"Log.hpp"
#include"Socket.hpp"
#include<signal.h>
#include<functional>

using func_t = std::function<std::string (std::string & package)>;


class TcpServer
{
public:
    TcpServer(){}

     TcpServer(const uint16_t & port,func_t fun):_port(port),callback_(fun)
     {}
    bool ServerInit()
    {
        _listensock.Socket();
        _listensock.Bind(_port);
        _listensock.Listen();
        log.LogMessage(INFO,"server init ... done");
        return true;
    }

    void Start()
    {
        signal(SIGCHLD,SIG_IGN);
        signal(SIGPIPE,SIG_IGN);
        while(true)
        {
            std::string serverip;
            uint16_t serverport;
            int sockfd = _listensock.Accept(&serverip,&serverport);
            if(sockfd<0)
            {
                continue;
            }
            log.LogMessage(INFO,"accept a new link,sockfd: %d, clientip: %s, clientport: %d",sockfd,serverip.c_str(),serverport);
            //提供服务
            if(fork() == 0)
            {
                _listensock.Close();
                std::string inbuffer_stream;
                //数据计算
                while(true)
                {
                    char buffer[128];
                    ssize_t n = read(sockfd,buffer,sizeof(buffer));
                    if(n>0)
                    {
                        buffer[n] = 0;
                        inbuffer_stream+=buffer;
                        log.LogMessage(DEBUG,"\n%s ",inbuffer_stream.c_str());
                        std::string info = callback_(inbuffer_stream);
                        if(info.empty()) continue;

                        write(sockfd,info.c_str(),info.size());
                    }
                    else if(n == 0) break;
                    else break;

                }

                exit(0);
            }
            close(sockfd);
        }
    }

    ~TcpServer(){}
private:
    uint16_t _port;
    Sock _listensock;
    func_t callback_;
};