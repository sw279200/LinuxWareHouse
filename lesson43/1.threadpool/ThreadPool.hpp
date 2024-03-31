#pragma once

#include"Thread.hpp"
#include"LockGuard.hpp"
#include"Log.hpp"
#include<pthread.h>
#include<functional>
#include<vector>
#include<queue>
#include<string>

const int defaultnum = 5;

class ThreadData
{
public:
    ThreadData(std::string name)
    :_threadname(name)
    {} 

    std::string GetThreadName()
    {
        return _threadname;
    }

    ~ThreadData(){}
private:
    std::string _threadname;
};

template<class T>
class ThreadPool
{
public:
    ThreadPool(int thread_num = defaultnum)
    :_thread_num(thread_num)
    ,_threads()
    {
        pthread_mutex_init(&_mutex,nullptr);
        pthread_cond_init(&_cond,nullptr);
        //构建指定个数的线程
        for(int i = 0;i<_thread_num;i++)
        {
            std::string threadname = "thread-";
            threadname+=std::to_string(i+1);
            //待优化
            ThreadData td(threadname);
            // Thread<ThreadData> t(threadname,\
            // std::bind(&ThreadPool<T>::ThreadRun,this,std::placeholders::_1),td);
            // _threads.push_back(t);
            _threads.emplace_back(threadname,\
            std::bind(&ThreadPool<T>::ThreadRun,this,std::placeholders::_1),td);
            log.LogMessage(DEBUG,"%s is created...\n",threadname.c_str());
        }

    }

    void ThreadWait(ThreadData& td)
    {
        log.LogMessage(DEBUG,"no task %s is sleeping...\n",td.GetThreadName().c_str());
        pthread_cond_wait(&_cond,&_mutex);
    }

    void ThreadWakeUp()
    {
        //log.LogMessage(DEBUG,"have task %s is wakeup...\n",td.GetThreadName().c_str());
        pthread_cond_signal(&_cond);
    }


    bool Start()
    {     
        //启动
        for(auto & thread:_threads)
        {
            thread.Start();
            log.LogMessage(INFO,"%s is running ...\n",thread.ThreadName().c_str());
        }

        return true;

    }

    void ThreadRun(ThreadData& td)
    {   
        while(true)
        {
            T t;
            {
                LockGuard lockguard(&_mutex);
                while(_q.empty())
                {
                    ThreadWait(td);
                    log.LogMessage(DEBUG,"thread %s is wakeup...\n",td.GetThreadName().c_str());
                }
                t = _q.front();
                _q.pop();
            }
            //处理任务
            t();
            log.LogMessage(INFO,"%s handler task %s done, result is : %s\n",\
            td.GetThreadName().c_str(),t.PrintTask().c_str(),t.PrintResult().c_str());
        }
    }

    void Push(T& in)
    {
        log.LogMessage(DEBUG,"other thread push a task: %s\n",in.PrintTask().c_str());
        LockGuard lockguard(&_mutex);
        _q.push(in);
        ThreadWakeUp();
    }
    void Wait()
    {
        for(auto & thread:_threads)
        {
            thread.Join();
        }
    }

    ~ThreadPool()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }

private:
    std::queue<T> _q;
    std::vector<Thread<ThreadData>> _threads;
    int _thread_num;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;

};