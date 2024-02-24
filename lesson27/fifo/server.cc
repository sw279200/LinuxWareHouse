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

bool MakeFifo()
{
    int n = mkfifo(FILENAME,0666);
    if(n<0)
    {
        cerr<<"errno: "<<errno<<", errstring: "<<strerror(errno)<<endl;
        return false;
    }

    cout<<"mkfifo success ...read"<<endl;
    return true;
}

int main()
{
Start:
    int rfd = open(FILENAME,O_RDONLY);
    if(rfd < 0)
    {
        cerr<<"errno: "<<errno<<", errstring: "<<strerror(errno)<<endl;
        if(MakeFifo()) goto Start;
        else return 1;
    }

    cout<<"open fifo success ..."<<endl;
    char buffer[1024];

    while(true)
    {
        ssize_t s = read(rfd,buffer,sizeof(buffer)-1);
        if(s>0)
        {
            buffer[s] = 0;
            cout<<"Client say# "<<buffer<<endl;
        }
        else if(s == 0)
        {
            cout<<"client quit , server quit too!"<<endl;
            break;
        }
    }

    close(rfd);
    cout<<"close fifo success ..."<<endl;
    return 0;
}