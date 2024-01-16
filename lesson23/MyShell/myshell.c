#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<ctype.h>


#define NUM 1024
#define SIZE 64
#define SEP " "
//#define Debug 0

#define NoneRedir   0
#define OutputRedir 1
#define AppendRedir 2
#define InputRedir  3

int redir = NoneRedir;
char *filename = NULL;

int lastcode = 0;
char cwd[1024];
char enval[1024];
char *homepath()
{
    char *home = getenv("HOME");
    if(home) return home;
    else return (char*)".";
}

const char* getUsername()
{
    const char* name = getenv("USER");
    if(name) return name;
    else return "none";
}

const char* getHostName()
{
    const char* hostname = getenv("HOSTNAME");
    if(hostname) return hostname;
    else return "none";
}

const char* getCwd()
{
    const char* cwd = getenv("PWD");
    if(cwd) return cwd;
    else return "none";
}

int getUserCommand(char* command,int num)
{
        
    printf("[%s@%s %s]# ",getUsername(),getHostName(),getCwd());
    char* r = fgets(command,num,stdin);
    if(r==NULL) return -1;
    command[strlen(command)-1]='\0';
    return strlen(command);
}

void commandSplit(char* in,char * out[])
{

    int argc = 0;
    out[argc++] = strtok(in,SEP);
    while(out[argc++]=strtok(NULL,SEP));
#ifdef Debug
    for(int i = 0;out[i];i++)
    {
        printf("%d : %s\n",i,out[i]);
    }
#endif
}

int execute(char* argv[])
{

     pid_t id = fork();
     if(id<0) return -1;
     else if(id==0)//child
     {
         int fd = 0;
         if(redir==InputRedir)
         {
             fd = open(filename,O_RDONLY);
             dup2(fd,0);

         }
         else if(redir == OutputRedir)
         {
             fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
             dup2(fd, 1);
         }
         else if(redir == AppendRedir)
         {
             fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
             dup2(fd, 1);
         }
         else
         {
            //do nothing
         }   
         //exec command
         execvp(argv[0],argv);
         exit(1);
     }
     else
     {
        int status = 0;
        pid_t rid = waitpid(id,NULL,0);
        if(rid>0)
        {
            lastcode = WEXITSTATUS(status);
        }
     }
     return 0;
}


void cd(const char *path)
{
    chdir(path);
    char tmp[1024];
    getcwd(tmp, sizeof(tmp));
    sprintf(cwd, "PWD=%s", tmp); // bug
    putenv(cwd);
}

// 什么叫做内键命令: 内建命令就是bash自己执行的，类似于自己内部的一个函数！
// 1->yes, 0->no, -1->err
int doBuildin(char *argv[])
{
    if(strcmp(argv[0], "cd") == 0)
    {
        char *path = NULL;
        if(argv[1] == NULL) path=homepath();
        else path = argv[1];
        cd(path);
        return 1;
    }
    else if(strcmp(argv[0], "export") == 0)
    {
        if(argv[1] == NULL) return 1;
        strcpy(enval, argv[1]);
        putenv(enval); // ???
        return 1;
    }
    else if(strcmp(argv[0], "echo") == 0)
    {
        if(argv[1] == NULL){
            printf("\n");
            return 1;
        }
        if(*(argv[1]) == '$' && strlen(argv[1]) > 1){ 
            char *val = argv[1]+1; // $PATH $?
            if(strcmp(val, "?") == 0)
            {
                printf("%d\n", lastcode);
                lastcode = 0;
            }
            else{
                const char *enval = getenv(val);
                if(enval) printf("%s\n", enval);
                else printf("\n");
            }
            return 1;
        }
        else {
            printf("%s\n", argv[1]);
            return 1;
        }
    }
    else if(0){}

    return 0;
}

#define SkipSpace(pos) do{ while(isspace(*pos)) pos++; }while(0)

void checkRedir(char usercommand[], int len)
{
    // ls -a -l > log.txt
    // ls -a -l >> log.txt
    char *end = usercommand + len - 1;
    char *start = usercommand;
    while(end>start)
    {
        if(*end == '>')
        {
            if(*(end-1) == '>')
            {
                *(end-1) = '\0';
                filename = end+1;
                SkipSpace(filename);
                redir = AppendRedir;
                break;
            }
            else
            {
                *end = '\0';
                filename = end+1;
                SkipSpace(filename);
                redir = OutputRedir;
                break;
            }
        }
        else if(*end == '<')
        {
            *end = '\0';
            filename = end+1;
            SkipSpace(filename); // 如果有空格，就跳过
        }
        else
        {
            end--;
        }
    }
}


int main()
{
    while(1)
    {
        
         char usercommand[NUM];
         char * argv[SIZE];
         //1.打印提示符&&获取用户命令字符串获取成功
         int n =  getUserCommand(usercommand,sizeof(usercommand));
         if(n<=0) continue;

		 checkRedir(usercommand, strlen(usercommand));
         //2.分割字符串
         commandSplit(usercommand,argv);
         //3.检查内建命令
         n = doBuildin(argv);
         if(n) continue;

         //4.执行对应的命令
         execute(argv);
    }
    return 0;
}
