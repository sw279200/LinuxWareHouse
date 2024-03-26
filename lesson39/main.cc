#include<iostream>
#include<string> 
#include<unistd.h>
#include"Thread.hpp"

std::string GetThreadName()
{
    static int num = 1;
    char name[64];
    snprintf(name,sizeof(name),"Thread-%d",num++);
    return name;
}

void Print(int num)
{
    while(num)
    {
        std::cout<<"hello world: "<<num--<<std::endl;
        sleep(1);
    }
}

int ticket = 10000;//全局的共享资源
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void GetTicket(std::string name)
{
    while(true)
    {
        pthread_mutex_lock(&mutex);
        if(ticket>0)
        {
            usleep(1000);
            printf("%s get a ticket: %d\n",name.c_str(),ticket);
            ticket--;
            pthread_mutex_unlock(&mutex);

        }
        else 
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
}

int main()
{
    std::string name1 = GetThreadName();
    Thread<std::string>t1(name1,GetTicket,name1);

    std::string name2 = GetThreadName();
    Thread<std::string>t2(name2,GetTicket,name2);

    std::string name3 = GetThreadName();
    Thread<std::string>t3(name3,GetTicket,name3);

    std::string name4 = GetThreadName();
    Thread<std::string>t4(name4,GetTicket,name4);

    t1.Start();
    t2.Start();
    t3.Start();
    t4.Start();

    t1.Join();
    t2.Join();
    t3.Join();
    t4.Join();


    // Thread<int> t(GetThreadName(),Print,10);
    // std::cout<<"thread is running? "<<t.IsRunning()<<std::endl;
    // t.Start();
    // std::cout<<"thread is running? "<<t.IsRunning()<<std::endl;
    // t.Join();
    return 0;
}