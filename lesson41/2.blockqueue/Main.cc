#include"BlockQueue.hpp"
#include<pthread.h>
#include<ctime>
#include<unistd.h>
#include<string>
#include"task.hpp"


void * consumer(void * args)
{
    BlockQueue<Task>* bq = static_cast<BlockQueue<Task>*>(args);
    while(true)
    {
        sleep(1);
        //1.拿数据  bq->pop(&data)
        Task t;
        bq->Pop(&t);
        //2.处理数据
        t.Run();
        std::cout<<"consumer Result: "<<t.PrintResult()<<std::endl;

        //消费者没有sleep
    }

    return nullptr;
}


void * productor(void * args)
{
    BlockQueue<Task>* bq = static_cast<BlockQueue<Task>*>(args);
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
        bq->Push(t);
        std::string task_string = t.PrintTask();
        std::cout<<"productor task: "<<task_string<<std::endl;

        sleep(1);

    }
    return nullptr;
}

int main()
{
    srand((uint16_t)time(nullptr) ^ getpid() ^ pthread_self());//只是为了生成更随机的数据
    BlockQueue<Task>* bq = new BlockQueue<Task>();
    pthread_t c,p;
    pthread_create(&p,nullptr,productor,bq);
    pthread_create(&c,nullptr,consumer,bq);
   

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);

    return 0;
}