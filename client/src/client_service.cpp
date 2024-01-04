//
// Created by lixiaoqing on 2021/5/27.
//

#include "client_service.h"

#include <memory>
#include <mutex>
#include <thread>

#include "log.h"

#define TAG "ClientService"

// 单例对象
static IClientService *singleton_client = nullptr;

// 互斥锁
static std::mutex singleton_mutex;


/**
 * 单例实现
 * @return
 */
IClientService *IClientService::GetSingleton() {
    if (singleton_client == nullptr) {
        std::unique_lock<std::mutex> lock(singleton_mutex);
        if (singleton_client == nullptr) {
            singleton_client = new ClientService();
        }
    }
    return singleton_client;
}

void IClientService::ReleaseSingleton() {
    if (singleton_client) {
        std::unique_lock<std::mutex> lock(singleton_mutex);
        if (singleton_client) {
            delete singleton_client;
            singleton_client = nullptr;
        }
    }
}

ClientService::ClientService() {
    Init();
}

ClientService::~ClientService() {
    Log::Info(TAG, "【析构】%s", __PRETTY_FUNCTION__);
    this->Disconnect();
}

void ClientService::Init() {
    // 初始化 Socket 监听器
    listener_ = std::make_shared<ClientListener>();

    // 初始化 Socket 对象智能指针
    client_ptr_ = std::make_shared<CTcpPackClientPtr>(listener_.get());

    // 拿到实际的 Socket 对象
    auto client = client_ptr_->Get();

    // 设置 Socket 通信缓冲区大小
    const unsigned int socket_buf_size = 1 * 1024 * 1024;  // 1MB
    client->SetSocketBufferSize(socket_buf_size);

    // 设置正常心跳包间隔。单位：毫秒
    const unsigned int keep_alive_time = 60 * 1000;
    client->SetKeepAliveTime(keep_alive_time);

    // 设置数据包最大长度（有效数据包最大长度不能超过 4194303/0x3FFFFF 字节，默认：262144/0x40000）
    client->SetMaxPackSize(0x1FFFFF);

    // 设置包头标识（有效包头标识取值范围 0 ~ 1023/0x3FF，当包头标识为 0 时不校验包头，默认：0）
    client->SetPackHeaderFlag(0x169);
}

bool ClientService::Connect(const char *const address, int port) {

    if (!client_ptr_) {
        Init();
        if (!client_ptr_) {
            Log::Info(TAG, "Socket 尚未初始化, 无法建立连接！");
            return false;
        }
    }

    auto client = client_ptr_->Get();

    // 先检查是否已连接
    bool is_ok = client->IsConnected();
    if (is_ok) {
        Log::Info(TAG, "Socket 连接已建立, 无需重复建立");
        return true;
    }

    // 建立 Socket 连接
    BOOL ret = client->Start(address, port, FALSE);
    if (ret == FALSE) {
        Log::Error(TAG, "Socket 连接失败！Error: %s", SYS_GetLastErrorStr());
        return false;
    }

    is_ok = client->IsConnected();
    if (is_ok) {
        Log::Info(TAG, "Socket 连接成功! [%s, %d] Socket ID=%lu", address, port, client->GetConnectionID());
    } else {
        Log::Error(TAG, "[%s, %d] Socket 连接失败！Error: %s", address, port, SYS_GetLastErrorStr());
    }

    return is_ok;
}

bool ClientService::Disconnect() {
    if (!client_ptr_) {
        Log::Warn(TAG, "Socket 连接为空");
        return true;
    }

    auto client = client_ptr_->Get();
    if (!client->IsConnected()) {
//        Log::Warn(TAG, "Socket 未连接！");
        return true;
    }

    // 关闭 Socket 连接
    BOOL ret = client->Stop();
    if (ret == FALSE) {
        Log::Info(TAG, "断开 Socket 连接失败！");
        return false;
    }

    Log::Info(TAG, "成功断开 Socket 连接！");
    return true;
}

void ClientService::Send(const BYTE *data, int length, OnSendSuccessCallback callback) {

    if (!client_ptr_) {
        Log::Info(TAG, "Socket 连接为空，发送数据失败！");
        return;
    }

    auto client = client_ptr_->Get();
    if (!client->IsConnected()) {
        Log::Info(TAG, "Socket 未连接，发送数据失败！");
        return;
    }

    Log::Info(TAG, "准备发送数据，数据长度: %dB", length);

    BOOL ret = FALSE;
    int retry_count = 0;

    const int kRetryTimes = 3;
    while (retry_count < kRetryTimes) {
        ++retry_count;
        // 向服务端发送数据
        ret = client->Send(data, length);
        if (ret == TRUE) {
            break;
        }
        Log::Info(TAG, "[第%d次]发送数据到服务端失败: %s", retry_count, SYS_GetLastErrorStr());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (ret == TRUE && callback) {
        // 处理发送成功的回调
        callback();
    }

    // 释放资源
    delete[] data;
}

void ClientService::Send(int data_type, const BYTE *data, int length, OnSendSuccessCallback callback) {
    Log::Info(TAG, "【发送】数据类型: %d, 数据长度: %dB", data_type, length);
    this->Send(data, length, callback);
}

bool ClientService::IsConnected() {
    return client_ptr_->Get()->IsConnected();
}
