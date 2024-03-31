#pragma once

#include <iostream>
#include <cstdarg>
#include <ctime>
#include <string>

enum
{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
    FATAL
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

class Log
{
public:
    Log() {}
    void LogMessage(int level, const char *format, ...) // 类c的日志接口
    {
        char content[1024];
        va_list args;
        va_start(args, format);
        vsnprintf(content, sizeof(content), format, args);
        va_end(args);
        uint64_t curtime = time(nullptr);
        printf("[level: %s][time: %s][content: %s]\n",LevelToString(level).c_str(),std::to_string(curtime).c_str(), content);
    }
    ~Log() {}

private:
};