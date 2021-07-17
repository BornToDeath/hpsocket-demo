//
// Created by lixiaoqing on 2021/7/17.
//

#include <memory>
#include <mutex>
#include "ServerService.h"
#include "ServerListener.h"
#include "Log.h"

#define TAG "ServerService"


static IServerService *serverSingleton = nullptr;
static std::mutex singletonMutex;


IServerService *IServerService::getSingleton() {
    if (serverSingleton == nullptr) {
        std::unique_lock<std::mutex> lock(singletonMutex);
        if (serverSingleton == nullptr) {
            serverSingleton = new ServerService();
        }
    }
    return serverSingleton;
}

void IServerService::releaseSingleton() {
    if (serverSingleton) {
        std::unique_lock<std::mutex> lock(singletonMutex);
        if (serverSingleton) {
            delete serverSingleton;
            serverSingleton = nullptr;
        }
    }
}

void ServerService::listen(int port) {
    auto listener = std::make_shared<ServerListener>();
    auto serverPtr = std::make_shared<CTcpPackServerPtr>(listener.get());

    auto server = serverPtr->Get();
    server->SetMaxPackSize(0x1FFFFF);
    server->SetPackHeaderFlag(0x169);
    server->SetKeepAliveTime(60 * 1000L);
    server->SetSocketBufferSize(1024 * 1024);
    auto ret = server->Start("127.0.0.1", port);
    if (ret == TRUE) {
        Log::info(TAG, "启动 Server 成功!");
    } else {
        Log::info(TAG, "启动 Server 失败!");
    }
}