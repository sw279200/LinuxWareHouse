#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int g_val = 100;

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child
        int cnt = 5;
        while(1)
        {
            printf("child, Pid: %d, Ppid: %d, g_val: %d, &g_val=%p\n", getpid(), getppid(), g_val, &g_val);
            sleep(1);
            if(cnt == 0)
            {
                g_val=200;
                printf("child change g_val: 100->200\n");
            }
            cnt--;
        }
    }
    else
    {
        //father
        while(1)
        {
            printf("father, Pid: %d, Ppid: %d, g_val: %d, &g_val=%p\n", getpid(), getppid(), g_val, &g_val);
            sleep(1);
        }
    }

    sleep(100);
    return 0;
}
