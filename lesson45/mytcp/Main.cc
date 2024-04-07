#include<memory>
#include<iostream>
#include"TcpServer.hpp"

void Usage(const std::string proc)
{
    std::cout<<"Usage: "<<proc<<" port[1024+]"<<std::endl;
}

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        Usage(argv[0]);
        exit(0);
    }
    uint16_t port = std::stoi(argv[1]);

    std::unique_ptr<TcpServer> tcp_svr(new TcpServer(port));
    tcp_svr->Init();
    tcp_svr->StartServer();
    return 0;
}