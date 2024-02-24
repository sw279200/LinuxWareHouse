#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include "comm.hpp"

class Init
{
public:
    Init()
    {
        // bool r = MakeFifo();
        // if (!r)
        //     return;

        key_t key = GetKey();
        std::cout << "key : " << ToHex(key) << std::endl;
        // sleep(3);
        // key vs shmid
        // shmid: 应用这个共享内存的时候，我们使用shmid来进行操作共享内存， FILE*
        // key: 不要在应用层使用，只用来在内核中标识shm的唯一性！， fd
        shmid = CreateShm(key);
        std::cout << "shmid: " << shmid << std::endl;

        // sleep(10);
        std::cout << "开始将shm映射到进程的地址空间中" << std::endl;

        s = (char *)shmat(shmid, nullptr, 0);
        // fd = open(filename.c_str(), O_RDONLY);
    }
    ~Init()
    {
        // sleep(5);
        shmdt(s);
        std::cout << "开始将shm从进程的地址空间中移除" << std::endl;

        // sleep(5);
        shmctl(shmid, IPC_RMID, nullptr);
        std::cout << "开始将shm从OS中删除" << std::endl;

        // close(fd);
        // unlink(filename.c_str());
    }

public:
    int shmid;
    int fd;
    char *s;
};

int main()
{
    key_t key = GetKey();
    // int msgid = msgget(key, IPC_CREAT | IPC_EXCL);
    // std::cout << "msgid: " << msgid << std::endl;
    // struct msqid_ds ds; 
    // msgctl(msgid, IPC_STAT, &ds);
    // std::cout << ds.msg_qbytes << std::endl;
    // std::cout << ToHex(ds.msg_perm.__key) << std::endl;
    // sleep(10);

     int semid = semget(key, 1, IPC_CREAT | IPC_EXCL);
     std::cout << "msgid: " << semid << std::endl;

     sleep(4);
     
     semctl(semid, 0, IPC_RMID);


    // msgctl(msgid, IPC_RMID, nullptr);


    // Init init;

    // struct shmid_ds ds;
    // shmctl(init.shmid, IPC_STAT, &ds);

    // std::cout << ToHex(ds.shm_perm.__key) << std::endl;
    // std::cout << ds.shm_segsz << std::endl;
    // std::cout << ds.shm_segsz << std::endl;
    // std::cout << ds.shm_segsz << std::endl;
    // std::cout << ds.shm_atime << std::endl;
    // std::cout << ds.shm_nattch << std::endl;

    // sleep(5);

    // TODO
    // while (true)
    // {
    //     // wait
    //     int code = 0;
    //     ssize_t n = read(init.fd, &code, sizeof(code));
    //     if (n > 0)
    //     {
    //         // 直接读取的
    //         std::cout << "共享内存的内容: " << init.s << std::endl;
    //         sleep(1);
    //     }
    //     else if (n == 0)
    //     {
    //         break;
    //     }
    // }

    // sleep(10);
    return 0;
}