#pragma once

#include"Thread.hpp"
#include"LockGuard.hpp"
#include"Log.hpp"
#include<pthread.h>
#include<functional>
#include<vector>
#include<queue>
#include<string>

const int defaultnum = 5;  //控制线程池中的线程数量

class ThreadData
{
public:
    ThreadData(std::string name) 
    :_threadname(name)
    {} 

    std::string GetThreadName()   //封装获取线程名字接口
    {
        return _threadname;
    }

    ~ThreadData(){}
private:
    std::string _threadname;//线程名称
};

template<class T>
class ThreadPool
{
public:

    void ThreadWait(ThreadData& td)//让线程阻塞
    {
        log.LogMessage(DEBUG,"no task %s is sleeping...\n",td.GetThreadName().c_str());
        pthread_cond_wait(&_cond,&_mutex);
    }

    void ThreadWakeUp()//唤醒一个线程
    {
        //log.LogMessage(DEBUG,"have task %s is wakeup...\n",td.GetThreadName().c_str());
        pthread_cond_signal(&_cond);
    }


    bool Start()
    {     
        //启动
        for(auto & thread:_threads)
        {
            thread.Start();//创建线程并启动
            log.LogMessage(INFO,"%s is running ...\n",thread.ThreadName().c_str());
        }

        return true;

    }

    void ThreadRun(ThreadData& td)//线程运行处理任务队列中的任务
    {   
        while(true)
        {
            T t;
            {
                LockGuard lockguard(&_mutex);
                while(_q.empty())//如果任务队列为空，那么就让进程停下来
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
        _q.push(in);//将任务放入任务队列
        ThreadWakeUp();//唤醒一个线程
    }
    void Wait()
    {
        for(auto & thread:_threads)
        {
            thread.Join();//让线程池中的线程一个一个的终止
        }
    }

    static ThreadPool<T>* GetInstance()
    {
        if(nullptr == instance)
        {
            instance = new ThreadPool<T>();
        }

        return instance;
    }

    ~ThreadPool()
    {
        pthread_mutex_destroy(&_mutex);//销毁锁
        pthread_cond_destroy(&_cond);//销毁环境变量
    }

private:
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
            threadname+=std::to_string(i+1);  //通过编号对线程进行动态命名
            //待优化
            ThreadData td(threadname);
            // Thread<ThreadData> t(threadname,\
            // std::bind(&ThreadPool<T>::ThreadRun,this,std::placeholders::_1),td);
            // _threads.push_back(t);
            _threads.emplace_back(threadname,\
            std::bind(&ThreadPool<T>::ThreadRun,this,std::placeholders::_1),td);
            log.LogMessage(DEBUG,"%s is created...\n",threadname.c_str());//打印日志消息
        }

    }

    ThreadPool(const ThreadPool<T> &tp) = delete;
    const ThreadPool<T> &operator=(const ThreadPool<T>) = delete;

private:
    std::queue<T> _q;//任务队列
    std::vector<Thread<ThreadData>> _threads;//用来存放线程的vector容器
    int _thread_num;//线程数量
    pthread_mutex_t _mutex;//互斥锁
    pthread_cond_t _cond;//条件变量

    static ThreadPool<T>* instance;

};

template<class T>
ThreadPool<T>* ThreadPool<T>::instance = nullptr;