#include"mystdio.h"
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#define DFL_MODE 0666


myFILE *my_fopen(const char* path,const char* mode)
{
    int fd = 0;
    int flag = 0;

    if(strcmp(mode,"r")==0)
    {
        flag |= O_RDONLY;
    }
    else if(strcmp(mode,"w")==0)
    {
        flag |= (O_WRONLY | O_CREAT | O_TRUNC);
    }
    else if(strcmp(mode,"a")==0)
    {
        flag |= (O_WRONLY | O_CREAT | O_APPEND);
    }
    else
    {
        //Do nothing
    }

    if(flag & O_CREAT)
    {
        fd = open(path,flag,DFL_MODE);

    }
    else 
    {
        fd = open(path,flag);
    }

    if(fd<0)
    {
        errno = 2;
        return NULL;
    }

    myFILE *fp = (myFILE*)malloc(sizeof(myFILE));
    if(!fp)
    {
        errno = 3;
        return NULL;
    }

    fp->flag = FLUSH_LINE;
    fp->end = 0;
    fp->fileno = fd;
    return fp;
}
int my_fwrite(const char* s,int num,myFILE *stream)
{
    //写入
    memcpy(stream->buffer+stream->end,s,num);
    stream->end+=num;
    //判断是否需要刷新
    if((stream->flag & FLUSH_LINE) && stream->end>0 && stream->buffer[stream->end-1]=='\n')
    {
        my_fflush(stream);
    }
    return num;
}
int my_fflush(myFILE *stream)
{

    if(stream->end>0)
    {
        write(stream->fileno,stream->buffer,stream->end);
        stream->end = 0;
    }
    return 0;
}
int my_fclose(myFILE *stream)
{
    my_fflush(stream);
    return close(stream->fileno);
}
