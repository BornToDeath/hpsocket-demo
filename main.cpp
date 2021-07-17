#include <iostream>
#include "IClientService.h"
#include "IServerService.h"
#include "Log.h"

#define TAG "Test"


int main() {

    // 在安卓设备上启动 server
    IServerService::getSingleton()->listen(9001);
    Log::info(TAG, "启动 Server !");

    // 在 Linux 设备上启动 client
    IClientService::getSingleton()->connect("127.0.0.1", 9000);
    Log::info(TAG, "启动 Client !");

    IClientService::releaseSingleton();
    IServerService::releaseSingleton();

    return 0;
}
