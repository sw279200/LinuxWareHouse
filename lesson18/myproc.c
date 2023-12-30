#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include<errno.h>
#define N 10

typedef  void (*callback_t)();

void Worker()
{
    int cnt = 10;
    while(cnt)
    {
        printf("I am a child process, pid: %d  ppid: %d, cnt: %d\n",getpid(),getppid(),cnt);
        sleep(1);
        --cnt;
    }
}


void createSubProcess(int n ,callback_t cb)
{
    int i = 0;
    for(;i<n;i++)
    {
        sleep(1);
        pid_t id = fork();
        if(id == 0)
        {
            printf("cearte child process success: %d\n",i);
            //child
            cb();
            exit(0);
        }
    }
}


int main()
{
    while(1)
    {
        printf("I am a nomal process  pid : %d\n",getpid());
        sleep(1);    
    }
  // int ret = 0;
  //  printf("before: %d\n", errno);
  //  FILE *fp = fopen("./log.txt", "r");
  //  if(fp == NULL) {
  //      printf("after: %d, error string : %s\n", errno, strerror(errno));
  //  }
   // int a = 10;
   // a/=0;
   //
   //int * p = NULL;
  // *p = 100;
    // int i = 0;
   // for(;i<200;i++)
   // {
   //     printf("%d : %s\n",i,strerror(i));
   // }

   // createSubProcess(N,Worker);
   //只有父进程走到这里
   // sleep(100);

    return 0 ;
}

