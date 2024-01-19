#include<stdio.h>
#include<string.h>
#include<unistd.h>


int main()
{
    fprintf(stdout,"hello fprintf\n");
    printf("C: hello printf\n");
    fputs("C: hello fputs\n",stdout);


    const char* str = "system call:hello write\n";
    write(1,str,strlen(str));

    fork();  //注意fork的位置
    return 0;
}
