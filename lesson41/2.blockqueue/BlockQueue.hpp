#pragma once

#include<iostream>
#include<queue>
#include<pthread.h>
#include"LockGuard.hpp"
const int Defaultcapacity = 5;

template<class T>
class BlockQueue
{
public:
    BlockQueue(int capacity=Defaultcapacity,int consumer_water_line=Defaultcapacity/5*3
    ,int productor_water_line=Defaultcapacity/5*3)
    :_capacity(capacity)
    ,_consumer_water_line(consumer_water_line)
    ,_productor_water_line(productor_water_line)
    {
        pthread_mutex_init(&_mutex,nullptr);
        pthread_cond_init(&_p_cond,nullptr);
        pthread_cond_init(&_c_cond,nullptr);
    }

    void Push(const T& in)
    {
        LockGuard lockguard(&_mutex);
        //pthread_mutex_lock(&_mutex);
        while(isFull())
        {
            //阻塞等待
            pthread_cond_wait(&_p_cond,&_mutex);
        }
        _q.push(in);
        // if(_q.size()>_productor_water_line)pthread_cond_signal(&_c_cond);
        pthread_cond_signal(&_c_cond);
        //pthread_mutex_unlock(&_mutex);
    }

    void Pop(T * out)
    {
        LockGuard lockguard(&_mutex);
        //pthread_mutex_lock(&_mutex);
        while(isEmpty())
        {
            //阻塞等待
            pthread_cond_wait(&_c_cond,&_mutex);
        }
        *out = _q.front();
        _q.pop();
        // if(_q.size()<_consumer_water_line)pthread_cond_signal(&_p_cond);
        pthread_cond_signal(&_p_cond);
        //pthread_mutex_unlock(&_mutex);
    }

    bool isFull(){return _q.size()==_capacity;}

    bool isEmpty(){return _q.size()==0;}

    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_p_cond);
        pthread_cond_destroy(&_c_cond);
    }



private:
    std::queue<T> _q;
    int _capacity;
    pthread_mutex_t _mutex;
    pthread_cond_t _p_cond;//生产者条件变量
    pthread_cond_t _c_cond;//消费者条件变量
    int _consumer_water_line;//消费者水位线
    int _productor_water_line;//生产者水位线
};