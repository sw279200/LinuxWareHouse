#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

void Worker()
{
    int cnt = 5;
    while(cnt)
    {
        printf("I am child process, pid : %d , ppid: %d, cnt: %d\n",getpid(),getppid(),cnt--);
        sleep(1);
    }
}


int main()
{
    pid_t id = fork();
    if(id==0)
    {
        //child
        Worker();
        exit(0);
    }
    else{
        sleep(10);
        //father
        pid_t rid = wait(NULL);
        if(rid==id)
        {
            printf("wait success! pid: %d\n",getpid());
        }
    }
    return 0;
}


//int func()
//{
//    printf("call fun function done!\n");
//   _exit(21);
//    // return 11;
//}

//int main()
//{
//    printf("you can see me!");
//    sleep(3);
//   _exit(1);
//   // _exit(31);
//   //  func();
//   // printf("I am a process , pid: %d , ppid: %d\n",getpid(),getppid());
//
//    //参数是进程的退出码，类似main函数中return n
//   // exit(12);
//
//    //1.在main函数中直接return
//   //2.在其他函数中进行return,表示的是函数调用结束
//   // return 21;
//}
