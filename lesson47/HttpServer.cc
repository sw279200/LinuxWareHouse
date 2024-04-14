#include "HttpServer.hpp"
#include<memory>
#include<iostream>


int main(int argv,char *argc[])
{
    if(argv!=2)
    {
        std::cerr<<"Usage: "<<argc[0]<<" port[1024+]"<<std::endl;
        exit(0);
    }

    uint16_t serverport = std::stoi(argc[1]);
    std::unique_ptr<HttpServer> svr(new HttpServer(serverport));
    svr->Start();
    return 0;
}