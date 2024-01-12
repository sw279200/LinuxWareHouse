#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    char * env_val = "MYVAL2=22222222222222222222222222";
    putenv(env_val);
    pid_t id = fork();
    if(id==0)
    {
        //child
      printf("pid: %d, exec command begin\n",getpid());
      execl("./mytest","mytest",NULL);
      // execl("/usr/bin/ls","ls","-a","-l",NULL);
     // // execl("/usr/bin/top","top",NULL);
     //// execl("/usr/bin/pwd","pwd",NULL);
      printf("pid: %d, exec command end\n",getpid());
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
