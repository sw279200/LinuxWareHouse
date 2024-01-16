#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define FILE_NAME "log.txt"


int main()
{
    
    int fd = open(FILE_NAME,O_WRONLY | O_CREAT | O_TRUNC,0666);
    if(fd<0)
    {
        perror("open error\n");
        return 1;
    }

    dup2(fd,1);
    printf("hello printf\n");
    fprintf(stdout,"hello fprintf\n");

    close(fd);

    //char buffer[1024];
    //ssize_t s = read(0,buffer,1024);
    //if(s>0)
    //{
    //    buffer[s-1] = 0;
    //    //printf("echo# %s\n",buffer);
    //    write(1,buffer,strlen(buffer));
    //}
   

    //close(0);
    //int fd = open(FILE_NAME,O_RDONLY,0666);
    //if(fd<0)
    //{
    //    perror("open");
    //    return 1;
    //}
    //
    //char buffer[1024];
    //fread(buffer,1,sizeof(buffer),stdin);
    //printf("%s\n",buffer);
    //fprintf(stdout,"fd: %d\n",fd);
    //fprintf(stdout,"stdout->fd : %d\n",stdout->_fileno);
    //fflush(stdout);
    //close(fd);
    return 0;
}
