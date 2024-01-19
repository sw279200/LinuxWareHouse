#include"mystdio.h"
#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main()
{
    myFILE *fp = my_fopen("./log.txt","w");
    if(fp == NULL)
    {
        perror("my_fopen error");
        return 1;
    }

    int cnt = 20;
    const char* msg = "hello,this is my stdio lib";
    while(cnt--)
    {
       my_fwrite(msg,strlen(msg),fp);
       sleep(1);
    }

    my_fclose(fp);
    return 0;
}
