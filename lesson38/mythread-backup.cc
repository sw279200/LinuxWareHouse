#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<string>
#include<functional>
#include<time.h>
#include<vector>

std::string toHex(pthread_t tid)
{
    char id[64];
    snprintf(id,sizeof(id),"0x%lx",tid);
    return id;
}

void * threadRoutine(void * arg)
{
    //pthread_detach(pthread_self());
    // usleep(1000);
    // std::string name = static_cast<const char *>(arg);
    int cnt = 5;
    while(cnt--)
    {
        std::cout<<"thread is running..."<<std::endl;
        sleep(1); 
    }

    // return (void*)"thread-1 done";
    return nullptr;
    // pthread_exit(nullptr);
}

int main()
{
    pthread_t tid;
    pthread_create(&tid,nullptr,threadRoutine,(void *)"thread-1");
    sleep(5);

    pthread_detach(tid);
    // std::cout<<"main thread,  "<<" main thread id : "<<toHex(pthread_self())<<std::endl;
    int n = pthread_cancel(tid);
    std::cout<<"main thread cancel done, "<<"n : "<<n<<std::endl;

    void * ret = nullptr;
    n = pthread_join(tid,&ret);
    std::cout<<"main thread join done,"<<" n : "<<n<<"thread return : "<<(int64_t)ret<<std::endl;
    return 0;
}


// const int threadnum = 5;
// using func_t = std::function<void()>;

// class ThreadData
// {
// public:
//     ThreadData(const std::string name,const uint64_t ctime,func_t f)
//         :threadname(name),createtime(ctime),func(f)
//         {}
// public:
//     std::string threadname;
//     uint64_t createtime;
//     func_t func;
// };

// void Print()
// {
//     std::cout<<"我是线程执行的大任务的一部分"<<std::endl;
// }

// void * ThreadRoutine(void * args)
// {
//     int a = 10;
//     ThreadData *td = static_cast<ThreadData*>(args);
//     while(true)
//     {
//         std::cout<<"I am a new pthread"<<"threadname: "<<td->threadname<<"create time: "<<td->createtime<<std::endl;
//         td->func();
//         // if(td->threadname=="thread - 4")
//         // {
//         //     std::cout<<td->threadname<<" 触发了异常"<<std::endl;
//         //     a/=0;
//         // }
//         sleep(1);
//     }
// }


// int main()
// {
//     std::vector<pthread_t> pthreads;
//     for(int i = 0;i<threadnum;i++)
//     {
//         pthread_t tid;
//         char threadname[64];
//         snprintf(threadname,sizeof(threadname),"%s - %lu","thread",i+1);
//         ThreadData * td = new ThreadData(threadname,(uint64_t)time(nullptr),Print);
//         pthread_create(&tid,nullptr,ThreadRoutine,td);
//         pthreads.push_back(tid);
//         sleep(1);
        
//     }

//     for(const auto &tid : pthreads)
//     {
//         std::cout<<"thread id : "<<tid<<std::endl;
//     }
    
//     while(true)
//     {
//         std::cout<<"I am a main pthread"<<std::endl;
//         sleep(1);
//     }
//     return 0;
// }