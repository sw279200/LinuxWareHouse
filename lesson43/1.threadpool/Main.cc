#include <iostream>
#include <memory>
#include "task.hpp"
#include "ThreadPool.hpp"
#include <ctime>
int main()
{
    //单例模式下这样构造对象就不起作用了
    //std::unique_ptr<ThreadPool<Task>> tp(new ThreadPool<Task>());
    ThreadPool<Task>::GetInstance()->Start();//创建线程并在任务队列中拿任务执行
    srand((uint64_t)time(nullptr) ^ getpid()); //种下随机种子
    while (true)
    {
        int data1 = rand() % 10;
        usleep(rand() % 123);
        int data2 = rand() % 10;
        usleep(rand() % 123);
        char oper = opers[rand() % opers.size()];
        // 2.生产数据构造任务
        Task t(data1, data2, oper);
        ThreadPool<Task>::GetInstance()->Push(t);//将任务放入任务队列
        sleep(1);
    }
    ThreadPool<Task>::GetInstance()->Wait();
    return 0;
}