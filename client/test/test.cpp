//
// Created by lixiaoqing on 2021/5/20.
//

#include <sys/prctl.h>

#include <cstring>
#include <iostream>
#include <thread>

#include "iclient_service.h"
#include "log.h"

#define TAG "Test"

namespace Test {
void Connection() {
    auto client = IClientService::GetSingleton();
    if (!client->Connect("127.0.0.1", 12345)) {
        Log::Error(TAG, "connect failed.");
        return;
    }

    std::string text = "hello world";
    client->Send((const unsigned char *) text.c_str(), text.length(), []() {
        Log::Info(TAG, "send success!");
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    IClientService::ReleaseSingleton();
}
}

int main() {
    Test::Connection();
    Log::Info(TAG, "进程退出...");
    return 0;
}