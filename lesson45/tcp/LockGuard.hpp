#pragma once
#include<pthread.h>


//不定义锁，默认认为外部会给我们传入锁对象
class Mutex
{
public:
    Mutex(pthread_mutex_t * lock):_lock(lock)
    {}

    void Lock()
    {
        pthread_mutex_lock(_lock);//加锁
    }

    void Unlock()
    {
        pthread_mutex_unlock(_lock);//解锁
    }


    ~Mutex(){}

private:
    pthread_mutex_t * _lock;
};

//RAII风格的加锁方式

class LockGuard
{
public:
    LockGuard(pthread_mutex_t * lock):_mutex(lock)
    {
        _mutex.Lock();
    }

    ~LockGuard()
    {
        _mutex.Unlock();
    }

private:
    Mutex _mutex;
};
