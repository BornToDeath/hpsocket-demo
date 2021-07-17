//
// Created by lixiaoqing on 2021/7/17.
//

#include <cstdio>
#include <cstdarg>
#include "Log.h"


void Log::info(const char *tag, const char *format, ...) {
    char log[1024] = {0};
    va_list args;
    va_start(args, format);
    vsnprintf(log, sizeof(log), format, args);
    va_end(args);
    print(tag, log);
}

void Log::warn(const char *tag, const char *format, ...) {
    char log[1024] = {0};
    va_list args;
    va_start(args, format);
    vsnprintf(log, sizeof(log), format, args);
    va_end(args);
    print(tag, log);
}

void Log::error(const char *tag, const char *format, ...) {
    char log[1024] = {0};
    va_list args;
    va_start(args, format);
    vsnprintf(log, sizeof(log), format, args);
    va_end(args);
    print(tag, log);
}

void Log::print(const char *tag, const char *log) {
    const std::string now = getCurrentDateTime();
    printf("%s | %s | %s\n", now.c_str(), tag, log);
}


std::string Log::getCurrentDateTime() {
    const int size = 64;
    char now[size];
    time_t curTimestamp;
    // 获取时间戳
    time(&curTimestamp);
    // 转换为tm结构
    tm *timeinfo = localtime(&curTimestamp);
    // 格式化为标准时间
    const char *format = "%Y-%m-%d %H:%M:%S";
    strftime(now, size, format, timeinfo);
    std::string ret(now);
    return ret;
}