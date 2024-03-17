#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>

int gcnt = 100;

void * ThreadRoutine(void * arg)
{
    const char* threadname = (const char *)arg;
    while(true)
    {
        std::cout<<"I am a new thread: "<<threadname<<", pid: "
        <<getpid()<<"gcnt: "<<gcnt<<"&gcnt: "<<&gcnt<<std::endl;
        gcnt--;
        sleep(1);
    }
}

int main()
{
    pthread_t tid;
    pthread_create(&tid,nullptr,ThreadRoutine,(void*)"thread 0");   
    sleep(3);

    // pthread_t tid1;
    // pthread_create(&tid1,nullptr,ThreadRoutine,(void*)"thread 1");   
    // sleep(3);

    // pthread_t tid2;
    // pthread_create(&tid2,nullptr,ThreadRoutine,(void*)"thread 2");   
    // sleep(3);

    // pthread_t tid3;
    // pthread_create(&tid,nullptr,ThreadRoutine,(void*)"thread 3");   
    // sleep(3);
    //主线程
    while(true)
    {
        std::cout<<"I am a main thread, pid: "
        <<getpid()<<"gcnt: "<<gcnt<<"&gcnt: "<<&gcnt<<std::endl;
        sleep(1);
    }
    return 0;
}