#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>



void Worker(int number)
{
    int *p = NULL;
    int cnt = 10;
    while(cnt)
    {
        printf("I am child process, pid: %d, ppid: %d, cnt: %d, number: %d\n", getpid(), getppid(), cnt--, number);
        sleep(1);

        //*p = 100;
        //int a = 10;
        //a /= 0;
    }
}

const int n = 10;

int main()
{

    for(int i = 0;i < n; i++)
    {
        pid_t id = fork();
        if(id == 0)
        {
            Worker(i);
            //status = i;
            exit(0);
        }
    }

    //等待多个子进程？
    for(int i = 0; i < n; i++)
    {
        int status = 0;
        pid_t rid = waitpid(-1, &status, 0); // pid>0, -1:任意一个退出的子进程
        if(rid > 0){
            printf("wait child %d success, exit code: %d\n", rid, WEXITSTATUS(status));
        }
    }
   // pid_t id = fork();
   // if(id==0)
   // {
   //     //child
   //     Worker();
   //     exit(1);
   // }
   // else{
   //    // sleep(10);
   //     //father
   //     printf("wait before!\n");
   //    // pid_t rid = wait(NULL);
   //     int status = 0;
   //     pid_t rid = waitpid(id,&status,0);

   //     printf("wait after!\n");
   //     if(rid==id)
   //     {
   //         printf("wait success! pid: %d rpid : %d,  exit sig: %d,  exit code: %d\n",getpid(),rid,status&0x7F,(status>>8)&0xFF);
   //     }

   //    // sleep(10);
   // }
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
