#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<string>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int ticket = 1000;


void * threadRoutine(void * args)
{
    std::string name = static_cast<const char *>(args);
    while(true)
    {
        pthread_mutex_lock(&mutex);
        if(ticket>0)
        {
            std::cout<<name<<", get a ticket :"<<ticket--<<std::endl;
            usleep(1000);
        }
        else
        {
            std::cout<<"没有票了，"<<name<<std::endl;
            pthread_cond_wait(&cond,&mutex);
        }
        pthread_mutex_unlock(&mutex);

        //sleep(1);
    }
}


int main()
{
    pthread_t t1,t2,t3;
    pthread_create(&t1,nullptr,threadRoutine,(void*)"thread-1");
    pthread_create(&t2,nullptr,threadRoutine,(void*)"thread-2");
    pthread_create(&t3,nullptr,threadRoutine,(void*)"thread-3");

    while(true)
    {
        sleep(6);     
        pthread_mutex_lock(&mutex);
        ticket+=1000;
        //pthread_cond_broadcast(&cond);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(t1,nullptr);
    pthread_join(t2,nullptr);
    pthread_join(t3,nullptr);
    return 0;
}