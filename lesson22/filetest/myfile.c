#include<stdio.h>

int main()
{
    //"w":按照写的方式打开文件，如果文件不存在就创建它
    //
    FILE *fp = fopen("log.txt","w");
    if(fp==NULL)
    {
        perror("fopen\n");
        return 1;

    }

    fclose(fp);
    
    return 0;
}
