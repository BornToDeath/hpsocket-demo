//
// Created by lixiaoqing on 2021/7/17.
//

#ifndef HPSOCKET_LOG_H
#define HPSOCKET_LOG_H


#include <string>


class Log final {

public:

    static void info(const char *tag, const char *format, ...);

    static void warn(const char *tag, const char *format, ...);

    static void error(const char *tag, const char *format, ...);

private:

    static void print(const char *tag, const char *log);

    static std::string getCurrentDateTime();

};


#endif //HPSOCKET_LOG_H