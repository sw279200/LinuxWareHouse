#include"UdpServer.hpp"
#include<memory>
#include<iostream>


int main(int argv, char* argc[])
{
    if(argv != 2)
    {
        log.LogMessage(ERROR,"Hint : Please Use %s  port[1024+] run",argc[0]);
        exit(0);
    }

    uint16_t port = std::stoi(argc[1]);

    std::unique_ptr<UdpServer> udpsvr(new UdpServer(port));
    udpsvr->Init();
    udpsvr->Run();

    return 0;
}