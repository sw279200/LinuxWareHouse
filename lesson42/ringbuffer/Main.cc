#include "RingQueue.hpp"
#include<pthread.h>
#include<unistd.h>
#include"task.hpp"
#include<ctime>
#include"Log.hpp"
class ThreadData
{
public:
    ThreadData(const std::string & name,RingQueue<Task>* rq)
    : threadname(name)
    ,_rq(rq)
    {}

    RingQueue<Task> * getRQ()
    {
        return this->_rq;
    }

    void setRQ(RingQueue<Task>* rq)
    {
        this->_rq = rq;
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
    RingQueue<Task>* _rq;
};


void * productor(void * args)
{
    ThreadData* td = static_cast<ThreadData*>(args);
    //sleep(5);
    while(true)
    {
        int data1 = rand()%10;
        usleep(rand()%123);
        int data2 = rand()%10;
        usleep(rand()%123);
        char oper = opers[rand() % opers.size()];
        //2.生产数据 
        Task t(data1,data2,oper);
        td->getRQ()->Push(t);
        std::string task_string = t.PrintTask();
        std::cout<<"productor task: "<<task_string<<" threadname: "<<td->getName()<<std::endl;
        //rq->push();
        sleep(1);
    }

    return nullptr;
}

void * consumer(void * args)
{
    ThreadData* td = static_cast<ThreadData*>(args);
    while(true)
    {
        //sleep(1);
        //rq->pop();
        Task t;
        td->getRQ()->Pop(&t);
        t();
        std::cout<<"consumer Result: "<<t.PrintResult()<<" threadname: "<<td->getName()<<std::endl;
    }

    return nullptr;
}

int main()
{

    Log log;
    log.LogMessage(DEBUG,"hello, %s ,%d ,%f","linux",109,3.1415926);
    log.LogMessage(INFO,"hello, %s ,%d ,%f","linux",109,3.1415926);
    log.LogMessage(WARNING,"hello, %s ,%d ,%f","linux",109,3.1415926);
    log.LogMessage(DEBUG,"hello, %s ,%d ,%f","linux",109,3.1415926);
    log.LogMessage(FATAL,"hello, %s ,%d ,%f","linux",109,3.1415926);
    log.LogMessage(8,"hello, %s ,%d ,%f","linux",109,3.1415926);

//     srand((uint64_t)time(nullptr) ^ getpid() ^ pthread_self());//只是为了生成更随机的数据
//     pthread_t c[3],p[2];
//     RingQueue<Task>* rq = new RingQueue<Task>();
//    ThreadData td1("consumer-1",rq),td2("consumer-2",rq),td3("consumer-3",rq),td4("productor-1",rq),td5("productor-2",rq);

//     pthread_create(&p[0],nullptr,productor,&td4);
//     pthread_create(&p[1],nullptr,productor,&td4);
//     pthread_create(&c[0],nullptr,consumer,&td1);
//     pthread_create(&c[1],nullptr,consumer,&td2);
//     pthread_create(&c[2],nullptr,consumer,&td3);

//     pthread_join(c[0],nullptr);
//     pthread_join(c[1],nullptr);
//     pthread_join(c[2],nullptr);
//     pthread_join(p[0],nullptr);
//     pthread_join(p[1],nullptr);
    return 0;
}
