#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<cstdlib>

// static void Usage(const std::string & proc)
// {
//     std::cout<<"\nUsage: "<<proc<<" signumber process\n"<<std::endl;
// }

int cnt = 0;
int n = 0;

void handler(int signo)
{
    n = alarm(0);
    std::cout<<"result: "<<n<<std::endl;
    //std::cout<<"get a signo: "<<signo<<"alarm : "<<cnt++<<std::endl;
    exit(0);
}

int main(int argc,char* argv[])
{
    signal(14,handler);
    std::cout<<"pid: "<<getpid()<<std::endl;
    alarm(30);

    while(true)
    {
        cnt++;
    }

    // int *p = nullptr;
    // *p = 100;
    
    // if(argc != 3)
    // {
    //     Usage(argv[0]);
    //     exit(0);
    // }

    // int signumber = std::stoi(argv[1]+1);
    // int processid = std::stoi(argv[2]);

    // kill(processid,signumber);

   

    // while(true)
    // {
    //     std::cout<<"running ...,pid: "<<getpid()<<std::endl;
    //     sleep(1);
    // }
    return 0;
}