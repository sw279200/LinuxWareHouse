#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<cstring>
#include"comm.hpp"
int main()
{
    key_t key = GetKey();
    int shmid = GetShm(key);
    char *s = (char*)shmat(shmid,nullptr,0);
    
    // char c = 'a';
    // for(;c<='z';c++)
    // {
    //     s[c-'a'] = c;
    //     std::cout<<"write: "<<c<<" done"<<std::endl;
    //     sleep(6);
    // }

    char arr[20] = "i am process A";
    for(int i = 0;i<strlen(arr);i++)
    {
        s[i] = arr[i];
        std::cout<<"write: "<<arr[i]<<" done"<<std::endl;
        sleep(2);
    }


    shmdt(s);
    std::cout<<"detach shm done"<<std::endl;
    return 0;
}