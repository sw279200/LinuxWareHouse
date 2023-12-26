#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
     while(1)
    {
        printf("I am a process: %d\n", getpid());
        sleep(1);
    }
    //pid_t id = fork();
    //if(id < 0) return 1;
    //else if(id == 0)
    //{
    //    // 子进程
    //    while(1)
    //    {
    //        printf("I am child ... \n");
    //        sleep(1);
    //    }
    //}
    //else{
    //    // 父进程
    //    int cnt = 5;
    //    while(cnt)
    //    {
    //        printf("I am father, run times: %d\n", cnt--);
    //        sleep(1);
    //    }

    //    printf("I am father, dead!: %d\n", cnt--);

    //    exit(2);
    //    // 回收操作，后面说
    //}
    //pid_t id = fork();
    //if(id < 0) return 1;
    //else if(id == 0)
    //{
    //    // 子进程
    //    int cnt = 5;
    //    while(cnt)
    //    {
    //        printf("I am child, run times: %d\n", cnt--);
    //        sleep(1);
    //    }

    //    printf("I am child, dead!: %d\n", cnt--);

    //    exit(2);
    //}
    //else{
    //    // 父进程
    //    while(1)
    //    {
    //        printf("I am father ... \n");
    //        sleep(1);
    //    }
    //    // 回收操作，后面说
    //}
  return 0;
}
