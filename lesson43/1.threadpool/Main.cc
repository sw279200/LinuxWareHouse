#include <iostream>
#include <memory>
#include "task.hpp"
#include "ThreadPool.hpp"
#include <ctime>
int main()
{
    std::unique_ptr<ThreadPool<Task>> tp(new ThreadPool<Task>());
    tp->Start();
    srand((uint64_t)time(nullptr) ^ getpid());
    while (true)
    {
        int data1 = rand() % 10;
        usleep(rand() % 123);
        int data2 = rand() % 10;
        usleep(rand() % 123);
        char oper = opers[rand() % opers.size()];
        // 2.生产数据
        Task t(data1, data2, oper);
        tp->Push(t);
        sleep(1);
    }
    tp->Wait();
    return 0;
}