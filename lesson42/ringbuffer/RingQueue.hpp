#pragma once

#include <iostream>
#include <vector>
#include <semaphore.h>
#include "LockGuard.hpp"
const int defaultsize = 5;
const int DefaultValue = 0;

template <class T>
class RingQueue
{
public:
    RingQueue(int size = defaultsize)
        : ringqueue(size), _size(size), _p_index(DefaultValue), _c_index(DefaultValue)
    {
        sem_init(&_space_sem, 0, size);
        sem_init(&_data_sem, 0, 0);
        pthread_mutex_init(&_p_mutex, nullptr);
        pthread_mutex_init(&_c_mutex, nullptr);
    }

    void Push(const T &in)
    {
        // 生产
        P(_space_sem);
        {
            LockGuard lockguard(&_p_mutex);
            ringqueue[_p_index] = in;
            _p_index++;
            _p_index %= _size;
        }
        V(_data_sem);
    }

    void Pop(T *out)
    {
        // 消费
        P(_data_sem);
        {
            LockGuard lockguard(&_c_mutex);

            *out = ringqueue[_c_index];
            _c_index++;
            _c_index %= _size;
        }
        V(_space_sem);
    }

    ~RingQueue()
    {
        sem_destroy(&_space_sem);
        sem_destroy(&_data_sem);

        pthread_mutex_destroy(&_p_mutex);
        pthread_mutex_destroy(&_c_mutex);
    }

private:
    void P(sem_t &sem)
    {
        sem_wait(&sem);
    }

    void V(sem_t &sem)
    {
        sem_post(&sem);
    }

private:
    std::vector<T> ringqueue;
    int _size;
    sem_t _space_sem;
    sem_t _data_sem;
    int _p_index;
    int _c_index;
    pthread_mutex_t _p_mutex;
    pthread_mutex_t _c_mutex;
};