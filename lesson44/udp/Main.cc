#include"UdpServer.hpp"
#include<memory>
#include<iostream>

void Usage(std::string proc)
{
    std::cout<<"\n\rUsage: "<<proc<<" port[1024+]\n"<<std::endl;
}

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        Usage(argv[0]);
        exit(1);
    }

    uint16_t port = std::stoi(argv[1]);

    std::unique_ptr<UdpServer> svr(new UdpServer(port));
    svr->Init();
    svr->Run();    
    return 0;
}