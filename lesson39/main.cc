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

int main()
{
    Thread<int> t(GetThreadName(),Print,10);
    std::cout<<"thread is running? "<<t.IsRunning()<<std::endl;
    t.Start();
    std::cout<<"thread is running? "<<t.IsRunning()<<std::endl;
    t.Join();
    return 0;
}