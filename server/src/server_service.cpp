//
// Created by lixiaoqing on 2021/7/17.
//

#include "server_service.h"

#include <memory>
#include <mutex>

#include "log.h"
#include "server_listener.h"

#define TAG "ServerService"

static IServerService *singleton_server = nullptr;
static std::mutex singleton_mutex;

IServerService *IServerService::GetSingleton() {
    if (singleton_server == nullptr) {
        std::unique_lock<std::mutex> lock(singleton_mutex);
        if (singleton_server == nullptr) {
            singleton_server = new ServerService();
        }
    }
    return singleton_server;
}

void IServerService::ReleaseSingleton() {
    if (singleton_server) {
        std::unique_lock<std::mutex> lock(singleton_mutex);
        if (singleton_server) {
            delete singleton_server;
            singleton_server = nullptr;
        }
    }
}

ServerService::ServerService() {
    auto listener = std::make_shared<ServerListener>();
    server_ = std::make_shared<CTcpPackServerPtr>(listener.get());
}

ServerService::~ServerService() {
    Stop();
}

bool ServerService::Listen(int port) {
    if (!server_) {
        Log::Error(TAG, "server 未创建!");
        return false;
    }
    auto server_ptr = server_->Get();
    server_ptr->SetMaxPackSize(0x1FFFFF);
    server_ptr->SetPackHeaderFlag(0x169);
    server_ptr->SetKeepAliveTime(60 * 1000L);
    server_ptr->SetSocketBufferSize(1024 * 1024);
    auto ret = server_ptr->Start("127.0.0.1", port);
    return ret == TRUE;
}

bool ServerService::Stop() {
    if (server_) {
        server_->Get()->Stop();
    }
}