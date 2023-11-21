#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    printf("我是一个父进程，pid是: %d, ppid是: %d\n",getpid(),getppid());

    fork();
    while(1)
    {

     sleep(1);
     printf("我是一个进程，pid是: %d, ppid是: %d\n",getpid(),getppid());
    }
    return 0;
}
