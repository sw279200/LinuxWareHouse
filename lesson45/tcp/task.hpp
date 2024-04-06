#pragma once
#include<string>
#include<iostream>
#include"Log.hpp"
#include"Init.hpp"

Init init;

class Task
{
public:
    Task(int sockfd, const uint16_t &clientport, const std::string &clientip)
    :clientip_(clientip),clientport_(clientport),sockfd_(sockfd)
    {}

    void Run()
    {
        char buffer[4096];
        // 测试代码
        ssize_t n = read(sockfd_, buffer, sizeof(buffer));
        if (n > 0)
        {
            buffer[n] = 0;
            std::cout << "client key# " << buffer << std::endl;
            std::string echo_string = init.translation(buffer);

            ssize_t w = write(sockfd_, echo_string.c_str(), echo_string.size());
            if(w<0)
            {
                log.LogMessage(WARNING,"write error ,errno:%d,strerror:%s",errno,strerror(errno));
            }
        }
        else if (n == 0)
        {
            log.LogMessage(INFO, "%s:%d quit,server close sockfd:%d", clientip_.c_str(), clientport_, sockfd_);
        
        }
        else
        {
            log.LogMessage(WARNING, "read error,sockfd:%d,clientip:%s ,clientport:%d ", sockfd_, clientip_.c_str(), clientport_);
            
        }
        close(sockfd_);
    }

    void operator()()//运算符重载实现仿函数
    {
        Run();
    }

    ~Task() {}
private:
    int sockfd_;
    std::string clientip_;
    uint16_t clientport_;
};
