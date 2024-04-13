#include "HttpServer.hpp"
#include<memory>
#include<iostream>


int main()
{
    std::unique_ptr<HttpServer> svr(new HttpServer());
    svr->Start();
    return 0;
}