#include<iostream>
#include<string> 
#include<unistd.h>
#include"Thread.hpp"
#include"LockGuard.hpp"
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
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
class ThreadData
{
public:
    ThreadData(const std::string & name,pthread_mutex_t* lock)
    : threadname(name)
    ,pmutex(lock)
    {}

    pthread_mutex_t * getPmutex()
    {
        return this->pmutex;
    }

    void setPmutex(pthread_mutex_t * mutex)
    {
        this->pmutex = mutex;
    }

    std::string getName()
    {
        return this->threadname;
    }

    void setName(std::string name)
    {
        this->threadname = name;
    }


private:
    std::string threadname;
    pthread_mutex_t * pmutex;
};

void GetTicket(ThreadData* td)
{
    while(true)
    {
        LockGuard lockguard(td->getPmutex());
        //pthread_mutex_lock(mutex);
        if(ticket>0)
        {
            usleep(1000);
            printf("%s get a ticket: %d\n",td->getName().c_str(),ticket);
            ticket--;
            //pthread_mutex_unlock(mutex);

        }
        else 
        {
            //pthread_mutex_unlock(mutex);
            break;
        }
    }
}



int main()
{
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,nullptr);

    std::string name1 = GetThreadName();
    ThreadData* td1 = new ThreadData(name1,&mutex);
    Thread<ThreadData*>t1(name1,GetTicket,td1);

    std::string name2 = GetThreadName();
    ThreadData* td2 = new ThreadData(name2,&mutex);
    Thread<ThreadData*>t2(name2,GetTicket,td2);

    std::string name3 = GetThreadName();
    ThreadData* td3 = new ThreadData(name3,&mutex);
    Thread<ThreadData*>t3(name3,GetTicket,td3);

    std::string name4 = GetThreadName();
    ThreadData* td4 = new ThreadData(name4,&mutex);
    Thread<ThreadData*>t4(name4,GetTicket,td4);

    t1.Start();
    t2.Start();
    t3.Start();
    t4.Start();

    t1.Join();
    t2.Join();
    t3.Join();
    t4.Join();
    
    pthread_mutex_destroy(&mutex);
    delete td1;
    delete td2;
    delete td3;
    delete td4;
    // Thread<int> t(GetThreadName(),Print,10);
    // std::cout<<"thread is running? "<<t.IsRunning()<<std::endl;
    // t.Start();
    // std::cout<<"thread is running? "<<t.IsRunning()<<std::endl;
    // t.Join();
    return 0;
}