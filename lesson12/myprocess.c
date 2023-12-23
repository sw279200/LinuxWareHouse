#include<stdio.h>

#include<sys/types.h>
#include<unistd.h>

int main()
{
    printf("我是一个进程 我的pid是：%d,ppid是：%d\n",getpid(),getppid());
   size_t id =  fork();
    
   if(id<0) return 1;
   else if(id==0)
   {
       while(1)
       {
           printf("我是一个子进程。pid:%d ppid:%d ret:%d  &id:%p,我正在执行下载任务\n",getpid(),getppid(),id,&id);
           sleep(1);
       }
   }
   else
   {
    
       while(1)
       {
           printf("我是一个父进程。pid:%d ppid:%d ret:%d &id:%p,我正在执行播放音乐任务\n",getpid(),getppid(),id,&id);
      sleep(2);
       }
   }
   

  //  while(1)
  //  {
  //      printf("我是一个进程 mypid:%d , ppid:%d fork  return id:%d\n",getpid(),getppid(),id);
  //      sleep(1);
  //  }
    return 0;
}
