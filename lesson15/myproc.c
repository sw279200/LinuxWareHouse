#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char* argv[])
{
    printf("PATH:%s\n",getenv("USER"));
   //int i = 4;
   //while(i--)
   // {
   //     printf("myself command!\n");
   // }

    // if(argc!=4)
   // {
   //     printf("Use error\nUsage: %s op[-add|sub|div|mul] d1 d2\n",argv[0]);
   //     return 1;
   // }
   // int x = atoi(argv[2]);
   // int y = atoi(argv[3]);
   // //你的程序一定有四个命令行参数，第一个是程序名
   // if(strcmp(argv[1],"-add")==0)
   // {
   //     printf("%d+%d=%d\n",x,y,x+y);
   // }
   // else if(strcmp(argv[1],"-sub")==0)
   // {
   //     printf("%d-%d=%d\n",x,y,x-y);
   // }
   // else if(strcmp(argv[1],"-mul")==0)
   // {
   //     printf("%d*%d=%d\n",x,y,x*y);
   // }
   // else if(strcmp(argv[1],"-div")==0)
   // {
   //    if(0==y)
   //    {
   //        printf("%d/%d=error! div zero\n",x,y);
   //    }
   //    else
   //      printf("%d/%d=%d\n",x,y,x/y);
   // }
   // else
   // {

   //     printf("Use error You should use right command line\nUsage: %s op[-add|sub|div|mul] d1 d2\n",argv[0]);
   // }
   // int i = 0;
   // for(;i<argc;i++)
   // {
   //     printf("%d: %s\n",i,argv[i]);
   // }
   // printf("hello world!\n");
    return 0;
}
