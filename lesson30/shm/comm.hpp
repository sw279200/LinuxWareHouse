#pragma once

#include<iostream>
#include<cstdlib>
#include<string>

const std::string pathname = "/home/sunwenchao/mylesson/lesson30";
const int proj_id = 0x11223344;
const int size = 4096;

key_t GetKey()
{
    key_t key = ftok(pathname.c_str(),proj_id);
    if(key<0)
    {
        std::cerr<<"errno: "<<errno <<", errstring: "<<strerror(errno)<<std::endl;
        exit(1);
    }
    std::cout<<"key: "<<key<<std::endl;
    return key;
}