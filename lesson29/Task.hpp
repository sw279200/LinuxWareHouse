#pragma once

#include<iostream>
#include<functional>
#include<ctime>
#include<unistd.h>
#include<vector>
using task_t = std::function<void()>;
//typedef std::function<void()> task_t;
void Download()
{
    std::cout<<"我是一个下载任务"<<" 处理者 ： "<<getpid()<<std::endl;
}

void PrintLog()
{
    std::cout<<"我是一个打印日志的任务"<<" 处理者 ： "<<getpid()<<std::endl;
}

void PushVideoStream()
{
    std::cout<<"这是一个推送视频流的任务"<<" 处理者 ： "<<getpid()<<std::endl;
}


class Init
{
public:

    //任务码
    const static int g_download_code = 1;
    const static int g_printlog_code = 2;
    const static int g_push_videostream_code = 3;

         //任务集合
    std::vector<task_t> tasks;
public:
    Init()
    {
        tasks.push_back(Download);
        tasks.push_back(PrintLog);
        tasks.push_back(PushVideoStream);
    }

    bool CheckSafe(int code)
    {
        if(code>=0&&code<tasks.size()) return true;
        else return false;
    }

    void RunTask(int code)
    {
        return tasks[code]();
    }

    int  SelectTask()
    {
        return rand()% tasks.size();
    }

    std::string ToDesc(int code)
    {
        switch(code)
        {
            case g_download_code:
            return "Download";
            case g_printlog_code:
            return "PrintLog";
            case g_push_videostream_code:
            return "PushVideoStream";
            default:
            return "Uknow";
        }
    }
};

Init init; //定义对象




