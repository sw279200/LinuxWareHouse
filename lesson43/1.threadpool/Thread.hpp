#pragma once
#include<iostream>
#include<string>
#include<functional>
#include<pthread.h>
template<class T>
using func_t = std::function<void(T&)>;//相当于typedef std::function<void()> func_t

template<class T>
class Thread
{
public:
    Thread(const std::string & threadname,func_t<T> func,T& data)//初始化线程对象
        :_tid(0)
        ,_isrunning(false)
        ,_threadname(threadname)
        ,_func(func)
        ,_data(data)
    {}

    static void* ThreadRoutine(void * args)  //线程创建时开始执行的函数是一个返回值为void* ,参数是一个void*的函数
    {
        Thread* ts =static_cast<Thread*>(args);
        ts->_func(ts->_data);

        return nullptr;
    }

    bool Start()
    {
        int n = pthread_create(&_tid,nullptr,ThreadRoutine,this);//创建线程同时获取返回值
        if(n==0)                        //通过创建线程函数返回值判断线程是否在运行。
        {
            _isrunning = true;
            return true;
        }
        return false;
    }

    bool Join()
    {
        if(!_isrunning) return true;    //如果线程没有运行就说明是终止成功了,所以返回true.
        int n = pthread_join(_tid,nullptr);//如果线程还在运行就让线程终止
        if(n==0)
        {
            _isrunning = false;//如果n==0说明终止线程成功了，返回true
            return true;
        }
        return false;//否则终止失败了
    }   

    std::string ThreadName()//向外提供线程名称的接口
    {
        return _threadname;
    }

    bool IsRunning()//向外提供判断线程是否正在运行的接口
    {
        return _isrunning;
    }

    ~Thread()
    {}

private:
    pthread_t _tid;//线程ID
    bool _isrunning;//判断线程是否正在运行
    std::string _threadname;//线程名称
    func_t<T> _func;//线程需要执行的函数
    T _data;//线程需要处理的数据
};