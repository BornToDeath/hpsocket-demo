//
// Created by lixiaoqing on 2021/7/17.
//

#ifndef HPSOCKET_LOG_H
#define HPSOCKET_LOG_H

#include <cstdarg>
#include <cstdio>
#include <string>

class Log final {
public:
    static void Info(const char *tag, const char *format, ...) {
        char log[1024] = {0};
        va_list args;
        va_start(args, format);
        vsnprintf(log, sizeof(log), format, args);
        va_end(args);
        Print(tag, log);
    }

    static void Warn(const char *tag, const char *format, ...) {
        char log[1024] = {0};
        va_list args;
        va_start(args, format);
        vsnprintf(log, sizeof(log), format, args);
        va_end(args);
        Print(tag, log);
    }

    static void Error(const char *tag, const char *format, ...) {
        char log[1024] = {0};
        va_list args;
        va_start(args, format);
        vsnprintf(log, sizeof(log), format, args);
        va_end(args);
        Print(tag, log);
    }


private:
    static void Print(const char *tag, const char *log) {
        const std::string now = CurrentDateTime();
        printf("%s | %s | %s\n", now.c_str(), tag, log);
    }

    static std::string CurrentDateTime() {
        const int size = 64;
        char now[size];
        time_t cur_timestamp;
        // 获取时间戳
        time(&cur_timestamp);
        // 转换为tm结构
        tm *timeinfo = localtime(&cur_timestamp);
        // 格式化为标准时间
        const char *format = "%Y-%m-%d %H:%M:%S";
        strftime(now, size, format, timeinfo);
        std::string ret(now);
        return ret;
    }
};


#endif //HPSOCKET_LOG_H