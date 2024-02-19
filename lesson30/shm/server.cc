#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<cstring>
#include"comm.hpp"
int main()
{
    key_t key = GetKey();
    int shmid = shmget(key,size,IPC_CREAT|IPC_EXCL);
    if(shmid<0)
    {
        std::cerr<<"errno: "<<errno <<", errstring: "<<strerror(errno)<<std::endl;
        return 1;
    }

    sleep(5);

    std::cout<<"shmid: "<<shmid<<std::endl;
    
    std::cout<<"开始将shm映射到进程的地址空间中 "<<std::endl;
    sleep(5);
    return 0;
}