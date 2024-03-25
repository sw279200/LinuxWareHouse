#pragma once
#include<iostream>
#include<string>
#include<functional>
#include<pthread.h>
template<class T>
using func_t = std::function<void(T)>;

template<class T>
class Thread
{
public:
    Thread(const std::string & threadname,func_t<T> func,T data)
        :_tid(0)
        ,_isrunning(false)
        ,_threadname(threadname)
        ,_func(func)
        ,_data(data)
    {}

    static void* ThreadRoutine(void * args)
    {
        Thread* ts =static_cast<Thread*>(args);
        ts->_func(ts->_data);

        return nullptr;
    }

    bool Start()
    {
        int n = pthread_create(&_tid,nullptr,ThreadRoutine,this);
        if(n==0)
        {
            _isrunning = true;
            return true;
        }
        return false;
    }

    bool Join()
    {
        if(!_isrunning) return true;
        int n = pthread_join(_tid,nullptr);
        if(n==0)
        {
            _isrunning = false;
            return true;
        }
        return false;
    }   

    std::string ThreadName()
    {
        return _threadname;
    }

    bool IsRunning()
    {
        return _isrunning;
    }

    ~Thread()
    {}

private:
    pthread_t _tid;
    bool _isrunning;
    std::string _threadname;
    func_t<T> _func;
    T _data;
};