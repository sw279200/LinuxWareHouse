#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>


int un_gval;//未初始化的全局变量
int init_gval = 10;//已初始化的全局变量

int main()
{

    printf("code addr: %p\n",main);//代码区
    const char* str="hello linux";
    printf("read only char addr: %p\n",str);//字符常量区
    printf("uninit global value addr: %p\n",&un_gval);//未初始化全局变量区
    printf("init global value addr: %p\n",&init_gval);//初始化全局变量区
    char * heap1 = (char*)malloc(100); 
    char * heap2 = (char*)malloc(100); 
    char * heap3 = (char*)malloc(100); 
    char * heap4 = (char*)malloc(100); 
    printf("heap1 addr: %p\n",heap1);//堆区
    printf("heap2 addr: %p\n",heap2);//堆区
    printf("heap3 addr: %p\n",heap3);//堆区
    printf("heap4 addr: %p\n",heap4);//堆区
    printf("stack addr: %p\n",&heap1);//栈区
    printf("stack addr: %p\n",&heap2);//栈区
    printf("stack addr: %p\n",&heap3);//栈区
    printf("stack addr: %p\n",&heap4);//栈区
    printf("stack addr: %p\n",&str);//栈区


   // extern char ** environ;
   // int i = 0;
   // for(;environ[i];i++)
   // {
   //     printf("pid: %d environ[%d]: %s\n",getpid(),i,environ[i]);
   // }
    return 0;
}
