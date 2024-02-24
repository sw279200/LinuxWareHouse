#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<cerrno>
#include<cstdlib>
#include<cstring>
#include<fcntl.h>
#include"comm.h"
using namespace std;

int main()
{
    int wfd = open(FILENAME,O_WRONLY);
    if(wfd<0)
    {
        cerr<<"errno: "<<errno<<", errstring: "<<strerror(errno)<<endl;
        return 1;
    }
    
    cout<<"mkfifo success ...write"<<endl;
    string message;
    message = "i am process A";
    ssize_t s = write(wfd,message.c_str(),message.size());
    if(s<0)
    {
        cerr<<"errno: "<<errno<<", errstring: "<<strerror(errno)<<endl;
    }
    close(wfd);
    cout<<"close fifo success ..."<<endl;
    return 0;
}