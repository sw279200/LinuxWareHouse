#include<stdio.h>


#define Print1 1               //0001
#define Print2 (1<<1)          //0010
#define Print3 (1<<2)          //0100
#define Print4 (1<<3)          //1000


void Print(int flags)
{
    if(flags&Print1) printf("hello 1\n");
    if(flags&Print2) printf("hello 2\n");
    if(flags&Print3) printf("hello 3\n");
    if(flags&Print4) printf("hello 4\n");
    else printf("None\n");
}

int main()
{
    Print(Print1);
    Print(Print1|Print2);
    Print(Print1|Print2|Print3);
    Print(Print3|Print4);
    Print(Print4);
    return 0;
}
