#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<cstring>
#include"comm.hpp"
int main()
{
    key_t key = GetKey();
    std::cout<<"key : "<<ToHex(key)<<std::endl;
    // sleep(3);
    int shmid = CreateShm(key);

    // sleep(5);

    std::cout<<"shmid: "<<shmid<<std::endl;
    
    std::cout<<"开始将shm映射到进程的地址空间中 "<<std::endl;
    char* s = (char*)shmat(shmid,nullptr,0);
    // sleep(5);

    while(true)
    {
        //直接读取
        std::cout<<"共享内存的内容："<<s<<std::endl;
        sleep(1);
    }


    std::cout<<"开始将shm从进程的地址空间中移除 "<<std::endl;
    shmdt(s);
    // sleep(5);

    shmctl(shmid,IPC_RMID,nullptr);
    std::cout<<"开始将shm从OS中删除 "<<std::endl;
    // sleep(10);
    return 0;
}