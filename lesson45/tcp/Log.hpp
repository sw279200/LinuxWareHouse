#pragma once

#include <iostream>
#include <cstdarg>
#include <ctime>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

enum
{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

enum
{
    Screen = 10,
    Onefile,
    Classfile
};

std::string LevelToString(int level)
{
    switch (level)
    {
    case DEBUG:
        return "Debug";
    case INFO:
        return "Info";

    case WARNING:
        return "Warning";
    case ERROR:
        return "Error";
    case FATAL:
        return "Fatal";
    default:
        return "Unknown";
    }
}

const int defaultstyle = Screen;
const std::string default_filename = "log.";
const std::string logdir="log";

class Log
{
public:
    Log():style(defaultstyle),filename(default_filename)
    {
        mkdir(logdir.c_str(),0775);
    }

    void Enable(int sty)
    {
        style = sty;
    }

    std::string TimestampToLocalTime()
    {
        time_t curr = time(nullptr);
        struct tm *currtime = localtime(&curr);
        char time_buffer[128];
        snprintf(time_buffer, sizeof(time_buffer), "%d-%d-%d %d:%d:%d",
                 currtime->tm_year + 1900, currtime->tm_mon, currtime->tm_mday, currtime->tm_hour,
                 currtime->tm_min, currtime->tm_sec);

        return time_buffer;
    }

    void WriteLog(const std::string &levelstr, const std::string &message)
    {
        switch (style)
        {
        case Screen:
            std::cout << message<<std::endl;
            break;
        case Onefile:
            WriteLogToOnefile("all", message);
            break;
        case Classfile:
            WriteLogToClassfile(levelstr, message);
            break;
        default:
            break;
        }
    }

    void WriteLogToOnefile(const std::string &logname, const std::string &message)
    {
        umask(0);
        int fd = open(logname.c_str(),O_CREAT | O_WRONLY | O_APPEND,0666);
        if(fd<0)return;
        write(fd,message.c_str(),message.size());
        close(fd);
        // std::ofstream out(logname);
        // if (!out.is_open())
        //     return;
        // out.write(message.c_str(), message.size());
        // out.close();
    }

    void WriteLogToClassfile(const std::string &levelstr, const std::string &message)
    {
        std::string logname = logdir;
        logname+="/";
        logname+=filename;
        logname += levelstr;
        WriteLogToOnefile(logname, message);
    }

    void LogMessage(int level, const char *format, ...) // 类c的日志接口
    {
        char rightbuffer[1024];
        va_list args;
        va_start(args, format);
        vsnprintf(rightbuffer, sizeof(rightbuffer), format, args);
        va_end(args);

        char leftbuffer[1024];
        std::string curtime = TimestampToLocalTime();
        std::string levelstr = LevelToString(level);
        std::string idstr = std::to_string(getpid());
        snprintf(leftbuffer, sizeof(leftbuffer), "[%s][%s][%s]",
                 levelstr.c_str(), curtime.c_str(), idstr.c_str());

        std::string logInfo = leftbuffer;
        logInfo += rightbuffer;

        WriteLog(levelstr, logInfo);
    }
    ~Log() {}

private:
    int style;
    std::string filename;
};


Log log;

class Conf
{
public:
    Conf()
    {
        log.Enable(Screen);
    }
    ~Conf(){}
};

Conf conf;