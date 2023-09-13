#include"code.h"

#define SIZE 101
#define MAXSIZE 100
#define STYLE '#'
#define CTIME 1000*40
const char* str = "|/-\\";



void process()
{
    //version 1
    int rate = 0;
    char c_str[SIZE] = {0};
    int len = strlen(str);
    while(rate<=MAXSIZE)
    {
        printf("[%-100s][%d%%][%c]\r",c_str,rate,str[rate%len]);
        fflush(stdout);
        usleep(CTIME); 
        c_str[rate++] = STYLE;
    }
    printf("\n");

}
