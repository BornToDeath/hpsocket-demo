//
// Created by lixiaoqing on 2021/5/27.
//

#ifndef CLIENT_CLIENT_SERVICE_H
#define CLIENT_CLIENT_SERVICE_H

#include <memory>

#include "hpsocket/HPTypeDef.h"
#include "hpsocket/SocketInterface.h"

#include "client_listener.h"
#include "iclient_service.h"

/**
 * Socket Client 客户端
 */
class ClientService final : public IClientService {
public:
    ClientService();

    ~ClientService() override;

    ClientService(const ClientService &client) = delete;

    ClientService &operator=(const ClientService *client) = delete;

private:
    /**
     * 连接服务端
     * @param address
     * @param port
     * @return
     */
    bool Connect(const char *address, int port) override;

    /**
     * 断开与服务端的连接并释放所有资源
     * @return
     */
    bool Disconnect() override;

    /**
     * 发送数据
     * @param data
     * @param length
     * @param callback
     * @return
     */
    void Send(const BYTE *data, int length, OnSendSuccessCallback callback) override;

    /**
     * 向服务端发送数据
     * @param data_type
     * @param data
     * @param length
     * @param callback
     * @return
     */
    void Send(int data_type, const BYTE *data, int length, OnSendSuccessCallback callback) override;

    /**
     * 接收服务端发来的数据
     */
    void Receive() override {}

    /**
     * 是否建立 Socket 连接
     * @return
     */
    bool IsConnected() override;

private:
    /**
     * Socket 连接之前的初始化工作
     */
    void Init();

private:
    /**
     * Socket 监听器
     */
    std::shared_ptr<ClientListener> listener_;

    /**
     * Socket Client 对象智能指针
     */
    std::shared_ptr<CTcpPackClientPtr> client_ptr_;

};


#endif //CLIENT_CLIENT_SERVICE_H