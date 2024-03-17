#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<string>
#include<functional>
#include<time.h>
#include<vector>

const int threadnum = 5;
using func_t = std::function<void()>;

class ThreadData
{
public:
    ThreadData(const std::string name,const uint64_t ctime,func_t f)
        :threadname(name),createtime(ctime),func(f)
        {}
public:
    std::string threadname;
    uint64_t createtime;
    func_t func;
};

void Print()
{
    std::cout<<"我是线程执行的大任务的一部分"<<std::endl;
}

void * ThreadRoutine(void * args)
{

   ThreadData *td = static_cast<ThreadData*>(args);
    while(true)
    {
        std::cout<<"I am a new pthread"<<"threadname: "<<td->threadname<<"create time: "<<td->createtime<<std::endl;
        td->func();
        sleep(1);
    }
}


int main()
{
    std::vector<pthread_t> pthreads;
    for(int i = 0;i<threadnum;i++)
    {
        pthread_t tid;
        char threadname[64];
        snprintf(threadname,sizeof(threadname),"%s - %lu","thread",i+1);
        ThreadData * td = new ThreadData(threadname,(uint64_t)time(nullptr),Print);
        pthread_create(&tid,nullptr,ThreadRoutine,td);
        pthreads.push_back(tid);
        sleep(1);
        
    }
    
      while(true)
    {
        std::cout<<"I am a main pthread"<<std::endl;
        sleep(1);
    }
    return 0;
}