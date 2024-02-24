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

std::string ToHex(int id)
{
    char buffer[1024];
    snprintf(buffer,sizeof(buffer),"0x%x",id);
    return buffer;
}

int CreateShmHelper(key_t key,int flag)
{
    int shmid = shmget(key,size,flag);
    if(shmid<0)
    {
        std::cerr<<"errno: "<<errno <<", errstring: "<<strerror(errno)<<std::endl;
        exit(2);
    }
    return shmid;
}

int CreateShm(key_t key)
{
    return CreateShmHelper(key,IPC_CREAT|IPC_EXCL|0644);
}

int GetShm(key_t key)
{
    return CreateShmHelper(key,IPC_CREAT);

}