#include<iostream>
#include<unistd.h>
#include<signal.h>

void PrintPending(const sigset_t &pending)
{
    for(int signo = 31;signo>0;signo--)
    {
        if(sigismember(&pending,signo))
        {
            std::cout<<"1";
        }
        else
        {
            std::cout<<"0";
        }

    }
    std::cout<<std::endl;
}

void handler(int signo)
{
    // sigset_t pending;

    // std::cout<<"###################"<<std::endl;
    // sigpending(&pending);
    // PrintPending(pending);

    // std::cout<<"###################"<<std::endl;

    std::cout<<"handler"<<signo<<std::endl;
}

int main()
{

    signal(2,handler);
    std::cout<<"getpid: "<<getpid()<<std::endl;

    //1.屏蔽2号信号
    sigset_t set,oset;
    sigemptyset(&set);
    sigemptyset(&oset);
    sigaddset(&set,2);
    sigprocmask(SIG_BLOCK,&set,&oset);

    //2.让进程不断获取当前进程的pending
    int cnt = 0;
    sigset_t pending;
    while(true)
    {
        sigpending(&pending);
        PrintPending(pending);

        sleep(1);
        
        cnt++;
        if(cnt==5)
        {
            std::cout<<"解除对2号信号的屏蔽，2号信号准备递达"<<std::endl;
            sigprocmask(SIG_SETMASK,&oset,nullptr);
        }
    }


    // std::cout<<"getpid: "<<getpid()<<std::endl;
    
    // signal(2,handler);

    // sigset_t block,oblock;

    // sigemptyset(&block);
    // sigemptyset(&oblock);


    // for(int signo = 1;signo<=31;signo++) sigaddset(&block,signo);

    // sigprocmask(SIG_SETMASK,&block,&oblock);

    // while(true)
    // {
    //     std::cout<<"我已经屏蔽了所有信号，来打我啊！"<<std::endl;
    //     sleep(1);
    // }



    return 0;
}