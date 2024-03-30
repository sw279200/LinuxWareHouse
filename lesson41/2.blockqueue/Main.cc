#include"BlockQueue.hpp"
#include<pthread.h>
#include<ctime>
#include<unistd.h>
#include<string>
#include"task.hpp"

class ThreadData
{
public:
    ThreadData(const std::string & name,BlockQueue<Task>* bq)
    : threadname(name)
    ,_bq(bq)
    {}

    BlockQueue<Task> * getBQ()
    {
        return this->_bq;
    }

    void setBQ(BlockQueue<Task>* bq)
    {
        this->_bq = bq;
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
    BlockQueue<Task>* _bq;
};

void * consumer(void * args)
{
    ThreadData* td = static_cast<ThreadData*>(args);
    while(true)
    {
        sleep(1);
        //1.拿数据  bq->pop(&data)
        Task t;
        td->getBQ()->Pop(&t);
        //2.处理数据
        t.Run();
        std::cout<<"consumer Result: "<<t.PrintResult()<<" threadname: "<<td->getName()<<std::endl;

        //消费者没有sleep
    }

    return nullptr;
}


void * productor(void * args)
{
    ThreadData* td = static_cast<ThreadData*>(args);

    while(true)
    {
        //1.有数据
        int data1 = rand()%10;
        usleep(rand()%123);
        int data2 = rand()%10;
        usleep(rand()%123);
        char oper = opers[rand() % opers.size()];
        //2.生产数据 
        Task t(data1,data2,oper);
        td->getBQ()->Push(t);
        std::string task_string = t.PrintTask();
        std::cout<<"productor task: "<<task_string<<" threadname: "<<td->getName()<<std::endl;

        sleep(1);

    }
    return nullptr;
}

int main()
{
    srand((uint16_t)time(nullptr) ^ getpid() ^ pthread_self());//只是为了生成更随机的数据
    BlockQueue<Task>* bq = new BlockQueue<Task>();
    pthread_t c[3],p[2];
    ThreadData td1("consumer-1",bq),td2("consumer-2",bq),td3("consumer-3",bq),td4("productor-1",bq),td5("productor-2",bq);

    pthread_create(&p[0],nullptr,productor,&td4);
    pthread_create(&p[1],nullptr,productor,&td4);
    pthread_create(&c[0],nullptr,consumer,&td1);
    pthread_create(&c[1],nullptr,consumer,&td2);
    pthread_create(&c[2],nullptr,consumer,&td3);
    

    pthread_join(c[0],nullptr);
    pthread_join(c[1],nullptr);
    pthread_join(c[2],nullptr);
    pthread_join(p[0],nullptr);
    pthread_join(p[1],nullptr);

    return 0;
}