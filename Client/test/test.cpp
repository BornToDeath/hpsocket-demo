//
// Created by lixiaoqing on 2021/5/20.
//

#include <iostream>
#include <thread>
#include <sys/prctl.h>
#include <cstring>
#include "Log.h"
#include "IClientService.h"
#include "Constants.h"
#include "DataWrapper.h"

#define TAG "Test"


namespace Test {

    void connection() {

        std::string logRootDir = "/home/lixiaoqing/AIDot/logs/";
        Log::init(logRootDir.c_str());

        // 服务端地址
        std::string serverAddress = Constants::SERVER_IP;
        int serverPort = Constants::SERVER_PORT;

        auto client = IClientService::getSingleton();
        client->connect(serverAddress.c_str(), serverPort);

        const std::string json = R"({"versionList":[{"name":"businessVersion","version":"100000"},{"name":"modelVersion","version":"200000"}]})";
        int jsonLen = static_cast<int>(json.length());
        Log::debug(TAG, "版本号json: %s", json.c_str());

        int length = 4 + 4 + jsonLen;
        auto data = new unsigned char[length]();

        int offset = 0;
        int dataType = 50;  // 版本号
        memcpy(data + offset, &dataType, 4);

        offset += 4;
        memcpy(data + offset, &jsonLen, 4);

        offset += 4;
        memcpy(data + offset, json.c_str(), jsonLen);

        {
            // 测试覆盖率
            BYTE *data1 = nullptr;
            int dataLen1;
            DataWrapper::wrap(dataType, data, length, &data1, dataLen1);

            BYTE *data2 = nullptr;
            int dataLen2;
            int dataType2;
            DataWrapper::parse(data1, dataLen1, dataType, &data2, dataLen2);

            delete[] data1;
            delete[] data2;

            IClientService::getSingleton()->isConnected();
        }

        const int MAX_COUNT = 20;
        int index = 0;
        while (index < MAX_COUNT) {
            auto dataSend = new unsigned char[length]();
            memcpy(dataSend, data, length);

            ++index;
            Log::info(TAG, "第 %d 次发送", index);
            client->send(dataType, dataSend, length, nullptr);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//            if (index == 200) {
//                break;
//            }
        }

        while (true) {
            Log::info(TAG, "休眠中...");
            std::this_thread::sleep_for(std::chrono::seconds(60));
            break;
        }

//        std::this_thread::sleep_for(std::chrono::seconds(20));
        Log::info(TAG, "--- 退出测试 ---");

        IClientService::getSingleton()->receive();
        delete[] data;
        IClientService::releaseSingleton();
    }

    void test02() {
        int num = 5;
        int length = sizeof(num);
        char *buf = new char[length];
        memcpy(buf, &num, length);

        SocketDataType type;
        char *outputData = nullptr;
        int outputLen = -1;
//    DataWrapper::parse(reinterpret_cast<const BYTE *>(buf), length, type, &outputData, outputLen);
//
//    int outputType = static_cast<std::underlying_type<SocketDataType>::type>(type);
//    Log::info(TAG, "输出类型=%d", outputType);
    }
}

int main() {

    // 设置线程名
    ::prctl(PR_SET_NAME, "SocketTest");

    // 测试
    Test::connection();

    Log::info(TAG, "进程退出...");

    return 0;
}