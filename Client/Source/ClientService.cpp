//
// Created by lixiaoqing on 2021/5/27.
//


/******** 引用头文件 ********/
#include <memory>
#include <mutex>
#include <thread>
#include "ClientService.h"
#include "Log.h"

/******** 宏定义 ********/
#define TAG "ClientService"


// 单例对象
static IClientService *clientSingleton = nullptr;

// 互斥锁
static std::mutex singletonMutex;


/**
 * 单例实现
 * @return
 */
IClientService *IClientService::getSingleton() {
    if (clientSingleton == nullptr) {
        std::unique_lock<std::mutex> lock(singletonMutex);
        if (clientSingleton == nullptr) {
            clientSingleton = new ClientService();
        }
    }
    return clientSingleton;
}

void IClientService::releaseSingleton() {
    if (clientSingleton) {
        std::unique_lock<std::mutex> lock(singletonMutex);
        if (clientSingleton) {
            delete clientSingleton;
            clientSingleton = nullptr;
        }
    }
}

ClientService::ClientService() {
    init();
}

ClientService::~ClientService() {
    Log::info(TAG, "【析构】%s", __PRETTY_FUNCTION__);
    this->disconnect();
}

void ClientService::init() {
    // 初始化 Socket 监听器
    listener = std::make_shared<ClientListener>();

    // 初始化 Socket 对象智能指针
    clientPtr = std::make_shared<CTcpPackClientPtr>(listener.get());

    // 拿到实际的 Socket 对象
    auto client = clientPtr->Get();

    // 设置 Socket 通信缓冲区大小
    const unsigned int socketBufSize = 1 * 1024 * 1024;  // 1MB
    client->SetSocketBufferSize(socketBufSize);

    // 设置正常心跳包间隔。单位：毫秒
    const unsigned int keepAliveTime = 60 * 1000;
    client->SetKeepAliveTime(keepAliveTime);

    // 设置数据包最大长度（有效数据包最大长度不能超过 4194303/0x3FFFFF 字节，默认：262144/0x40000）
    client->SetMaxPackSize(0x1FFFFF);

    // 设置包头标识（有效包头标识取值范围 0 ~ 1023/0x3FF，当包头标识为 0 时不校验包头，默认：0）
    client->SetPackHeaderFlag(0x169);
}

bool ClientService::connect(const char *const address, int port) {

    if (!clientPtr) {
        init();
        if (!clientPtr) {
            Log::info(TAG, "Socket 尚未初始化, 无法建立连接！");
            return false;
        }
    }

    auto client = clientPtr->Get();

    // 先检查是否已连接
    bool isOk = client->IsConnected();
    if (isOk) {
        Log::info(TAG, "Socket 连接已建立, 无需重复建立");
        return true;
    }

    // 建立 Socket 连接
    BOOL ret = client->Start(address, port, FALSE);
    if (ret == FALSE) {
        Log::error(TAG, "Socket 连接失败！Error: %s", SYS_GetLastErrorStr());
        return false;
    }

    isOk = client->IsConnected();
    if (isOk) {
        Log::info(TAG, "Socket 连接成功! [%s, %d] Socket ID=%lu", address, port, client->GetConnectionID());
    } else {
        Log::error(TAG, "[%s, %d] Socket 连接失败！Error: %s", address, port, SYS_GetLastErrorStr());
    }

    return isOk;
}

bool ClientService::disconnect() {
    if (!clientPtr) {
        Log::warn(TAG, "Socket 连接为空");
        return true;
    }

    auto client = clientPtr->Get();
    if (!client->IsConnected()) {
//        Log::warn(TAG, "Socket 未连接！");
        return true;
    }

    // 关闭 Socket 连接
    BOOL ret = client->Stop();
    if (ret == FALSE) {
        Log::info(TAG, "断开 Socket 连接失败！");
        return false;
    }

    Log::info(TAG, "成功断开 Socket 连接！");
    return true;
}

void ClientService::send(const BYTE *data, int length, onSendSuccessCallback callback) {

    if (!clientPtr) {
        Log::info(TAG, "Socket 连接为空，发送数据失败！");
        return;
    }

    auto client = clientPtr->Get();
    if (!client->IsConnected()) {
        Log::info(TAG, "Socket 未连接，发送数据失败！");
        return;
    }

    Log::info(TAG, "准备发送数据，数据长度: %dB", length);

    BOOL ret = FALSE;
    int retryCount = 0;

    const int RETRY_TIMES = 3;
    while (retryCount < RETRY_TIMES) {
        ++retryCount;
        // 向服务端发送数据
        ret = client->Send(data, length);
        if (ret == TRUE) {
            break;
        }
        Log::info(TAG, "[第%d次]发送数据到服务端失败: %s", retryCount, SYS_GetLastErrorStr());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (ret == TRUE && callback) {
        // 处理发送成功的回调
        callback();
    }

    // 释放资源
    delete[] data;
}

void ClientService::send(int dataType, const BYTE *data, int length, onSendSuccessCallback callback) {
    Log::info(TAG, "【发送】数据类型: %d, 数据长度: %dB", dataType, length);
    this->send(data, length, callback);
}

bool ClientService::isConnected() {
    return clientPtr->Get()->IsConnected();
}
