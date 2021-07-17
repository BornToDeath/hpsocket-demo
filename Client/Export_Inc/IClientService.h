//
// Created by lixiaoqing on 2021/5/27.
//

#ifndef AIDOT_ICLIENTSERVICE_H
#define AIDOT_ICLIENTSERVICE_H


#include <functional>
#include <memory>

using BYTE = unsigned char;


// 成功发送数据的回调
using onSendSuccessCallback = std::function<void(void)>;


/**
 * Socket Client 接口类，定义 Client 的一些功能
 */
class IClientService {

public:

    virtual ~IClientService() = default;

    /**
     * 单例
     * @return
     */
    static IClientService *getSingleton();

    /**
     * 单例释放
     */
    static void releaseSingleton();

    /**
     * 连接服务端
     * @param address 服务端 IP
     * @param port    服务端 Port
     * @return
     */
    virtual bool connect(const char *address, int port) = 0;

    /**
     * 断开与服务端的 Socket 连接并释放所有资源
     * @return
     */
    virtual bool disconnect() = 0;

    /**
     * 发送数据。发送之后会自动释放 data
     * @param data     待发送的数据
     * @param length   待发送数据的长度
     * @param callback 发送成功之后的处理
     * @return
     */
    virtual void send(const BYTE *data, int length, onSendSuccessCallback callback) = 0;

    /**
     * 向服务端发送数据
     * @param dataType
     * @param data
     * @param length
     * @param callback
     * @return
     */
    virtual void send(int dataType, const BYTE *data, int length, onSendSuccessCallback callback) = 0;

    /**
     * 接收服务端发来的数据
     */
    virtual void receive() = 0;

    /**
     * Socket 连接是否已建立
     * @return
     */
    virtual bool isConnected() = 0;

};


#endif //AIDOT_ICLIENTSERVICE_H
