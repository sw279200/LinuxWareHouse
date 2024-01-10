#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    pid_t id = fork();
    if(id==0)
    {
     execl("./mytest","mytest",NULL);
        //child
     // printf("pid: %d, exec command begin\n",getpid());
     //  execl("/usr/bin/ls","ls","-a","-l",NULL);
     // // execl("/usr/bin/top","top",NULL);
     // sleep(3);
     //// execl("/usr/bin/pwd","pwd",NULL);
     // printf("pid: %d, exec command end\n",getpid());
    // exit(1);
    }
    else
    {
        //father
        pid_t rid = waitpid(-1,NULL,0);
        if(rid>0)
        {
            printf("wait success , rid : %d\n",rid);
        }
    }
    return 0;
}
