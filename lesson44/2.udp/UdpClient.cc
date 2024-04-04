#include <memory>
#include<cstdio>
#include<errno.h>
#include<cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"


int main(int argv,char* argc[])
{
    if(argv != 3)
    {
        log.LogMessage(ERROR,"Hint : Please Use %s serverip serverport[1024+] run",argc[0]);
        exit(0);
    }

    std::string serverip = argc[1];
    uint16_t serverport = std::stoi(argc[2]);

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(serverip.c_str());
    server.sin_port = htons(serverport);
    socklen_t len = sizeof(server);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        log.LogMessage(FATAL, "create socket error, errno:%d , error string: %s", errno, strerror(errno));
        return 1;
    }
    log.LogMessage(INFO, "create socket success, errno:%d , error string: %s", errno, strerror(errno));

    char buffer[1024];
    std::string message;
    while(true)
    {
        std::cout<<"Please Enter# ";
        getline(std::cin,message);
        std::cout<<message<<std::endl;
        //通过键盘输入消息打包发给服务器
        sendto(sockfd,message.c_str(),message.size(),0,(struct sockaddr*)&server,len);

        struct sockaddr temp;
        socklen_t Len = sizeof(temp);
        ssize_t s = recvfrom(sockfd,buffer,1023,0,(struct sockaddr*)&temp,&Len);
        if(s>0)
        {
            buffer[s] = 0;
            std::cout<<buffer<<std::endl;
        }
    }

    close(sockfd);
    return 0;
}