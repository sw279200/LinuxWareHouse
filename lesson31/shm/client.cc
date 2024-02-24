#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/ipc.h> //Inter-Process Communication
#include <sys/shm.h>
#include "comm.hpp"

int main()
{
    key_t key = GetKey();
    int shmid = GetShm(key);
    char *s = (char*)shmat(shmid, nullptr, 0);
    std::cout << "attach shm done" << std::endl;
    int fd = open(filename.c_str(), O_WRONLY);

    // sleep(10);
    // TODO
    // 共享内存的通信方式，不会提供同步机制, 共享内存是直接裸露给所有的使用者的，一定要注意共享内存的使用安全问题
    // 
    char c = 'a';
    for(; c <= 'z'; c++)
    {
        s[c-'a'] = c;
        std::cout << "write : " << c << " done" << std::endl;
        sleep(1);

        // 通知对方
        int code = 1;
        write(fd, &code, sizeof(4));
    }

    shmdt(s);
    std::cout << "detach shm done" << std::endl;
    close(fd);
    return 0;
}