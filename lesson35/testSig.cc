#include<iostream>
#include<unistd.h>
#include<signal.h>

void Print(const sigset_t & pending);

void handler(int signo)
{
    std::cout<<"get a sig: "<<signo<<std::endl;
    sleep(1);
    // while(true)
    // {
    //     sigset_t pending;
    //     sigpending(&pending);
    //     Print(pending);
    //     sleep(1);
    // }
}

void Print(const sigset_t & pending)
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


int main()
{
    signal(2,handler);
    signal(3,handler);
    signal(4,handler);
    signal(5,handler);

    sigset_t mask,omask;
    sigemptyset(&mask);
    sigemptyset(&omask);

    sigaddset(&mask,2);
    sigaddset(&mask,3);
    sigaddset(&mask,4);
    sigaddset(&mask,5);

    sigprocmask(SIG_SETMASK,&mask,&omask);

    // std::cout<<"getpid: "<<getpid()<<std::endl;
    // struct sigaction act,oact;
    // act.sa_handler = handler;
    // sigemptyset(&act.sa_mask);
    // sigaddset(&act.sa_mask,3);

    // sigaction(2,&act,&oact);


    int cnt = 20;
    std::cout<<"getpid: "<<getpid()<<std::endl;
    while(true)
    {
        sigset_t pending;
        sigpending(&pending);
        Print(pending);
        cnt--;
        sleep(1);
        if(cnt==0)
        {
            sigprocmask(SIG_SETMASK,&omask,nullptr);
            std::cout<<"cancel 2, 3, 4, 5 block"<<std::endl;
        }
    }

    return 0;
}