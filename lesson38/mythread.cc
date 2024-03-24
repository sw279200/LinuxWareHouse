
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>

using namespace std;

// int g_val = 100; // 全局变量，本身就是被所有线程共享的
__thread int g_val = 100; // 线程的局部存储！有什么用？有什么坑？

__thread pid_t lwp = 0;

// __thread std::string threadname;

pid_t gettid() {
 return syscall(SYS_gettid);
}

void *threadRoutine(void *args)
{
    std::string name = static_cast<const char *>(args);
    lwp = gettid(); // 调用系统调用 SYS_gettid 获取当前线程的 TID
    while (true)
    {
        sleep(1);
        std::cout << name << ", g_val: " << g_val << " ,&g_val: " << &g_val << "\n"
                  << std::endl;
        std::cout <<"new thread: " << dec<<lwp << std::endl;
        g_val++;
    }

    return nullptr;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, threadRoutine, (void *)"thread1");
    lwp = gettid(); // 调用系统调用 SYS_gettid 获取当前线程的 TID
    std::cout <<"main thread: " << lwp << std::endl;

    while (true)
    {
        sleep(1);
        std::cout << "main thread, g_val: " << g_val << " ,&g_val: " << &g_val << "\n"
                  << std::endl;
    }
    pthread_join(tid, nullptr);
}