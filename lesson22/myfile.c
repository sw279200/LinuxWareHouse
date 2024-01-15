#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>




int main()
{

    printf("stdin->fd: %d\n",stdin->_fileno);
    printf("stdout->fd: %d\n",stdout->_fileno);
    printf("stderr->fd: %d\n",stderr->_fileno);

    FILE* fp =fopen("log.txt","w");
    printf("fp->fd: %d\n",fp->_fileno);
    fclose(fp);
    //int fd = open("log.txt",O_WRONLY | O_CREAT|O_APPEND,0666);
    //int fd1 = open("log1.txt",O_WRONLY | O_CREAT|O_APPEND,0666);
    //int fd2 = open("log2.txt",O_WRONLY | O_CREAT|O_APPEND,0666);
    //int fd3 = open("log3.txt",O_WRONLY | O_CREAT|O_APPEND,0666);
    //int fd4 = open("log4.txt",O_WRONLY | O_CREAT|O_APPEND,0666);

    //printf("fd1: %d\n",fd1);
    //printf("fd2: %d\n",fd2);
    //printf("fd3: %d\n",fd3);
    //printf("fd4: %d\n",fd4);

    //close(fd1);
    //close(fd2);
    //close(fd3);
    //close(fd4);
    //if(fd<0)
    //{
    //    perror("open error\n");
    //    return 1;
    //}
    //
    ////下面对文件进行操作
    //const char * msg = "bbbbbbbbbbbbb";

    //write(fd,msg,strlen(msg));

    //close(fd);

    return 0;
    //"w":按照写的方式打开文件，如果文件不存在就创建它
    //
    //FILE *fp = fopen("log.txt","a");
    //if(fp==NULL)
    //{
    //    perror("fopen\n");
    //    return 1;

    //}
    //
    //const char* msg = "bbbbbbbbbbbbbbbbbbbbbbbbbb\n";
    //fputs(msg,fp);
    // int cnt = 10;
    // while(cnt)
    // {
    //     fputs(msg,fp);
    //     cnt--;
    // }

    //fclose(fp);
    
}
