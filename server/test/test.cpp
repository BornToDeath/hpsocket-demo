#include <iostream>
#include <thread>

#include "iserver_service.h"
#include "log.h"

#define TAG "Test"

void TestServer() {
    auto server = IServerService::GetSingleton();
    if (!server) {
        Log::Error(TAG, "创建 server 失败！");
        return;
    }
    if (!server->Listen(12345)) {
        Log::Error(TAG, "启动 Server 失败!");
        return;
    }
    Log::Info(TAG, "启动 Server !");
    std::this_thread::sleep_for(std::chrono::seconds(60));
    IServerService::ReleaseSingleton();
}

int main() {
    TestServer();
    return 0;
}
