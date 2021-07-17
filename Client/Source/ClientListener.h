//
// Created by lixiaoqing on 2021/5/27.
//

#ifndef COMMUNICATION_CLIENTLISTENER_H
#define COMMUNICATION_CLIENTLISTENER_H


#include "hpsocket/HPSocket.h"


/**
 * Socket 事件监听器。定义一些事件的处理方法
 */
class ClientListener final : public CTcpClientListener {

public:

    ClientListener();

    ~ClientListener() override;

    /**
     * 名称：准备连接通知
     * 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听器将收到该通知，
     *      监听器可以在通知处理方法中执行 Socket 选项设置等额外工作
     * @param pSender  事件源对象
     * @param dwConnID 连接 ID
     * @param socket   客户端 Socket
     * @return HR_OK / HR_IGNORE  继续执行
     *         HR_ERROR           终止启动通信客户端组件
     */
    EnHandleResult OnPrepareConnect(ITcpClient *pSender, CONNID dwConnID, SOCKET socket) override;

    /**
     * 名称：连接完成通知
     * 描述：与服务端成功建立连接时，Socket 监听器将收到该通知
     * @param pSender  事件源对象
     * @param dwConnID 连接 ID
     * @return HR_OK / HR_IGNORE 继续执行
     *         HR_ERROR          同步连接：终止启动通信客户端组件；
     *                           异步连接：关闭连接
     */
    EnHandleResult OnConnect(ITcpClient *pSender, CONNID dwConnID) override;

    /**
     * 名称：握手完成通知
     * 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作
     * @param pSender  事件源对象
     * @param dwConnID 连接 ID
     * @return HR_OK / HR_IGNORE 继续执行
     *         HR_ERROR          引发 OnClose() 事件并关闭连接
     */
    EnHandleResult OnHandShake(ITcpClient *pSender, CONNID dwConnID) override;

    /**
     * 名称：已发送数据通知
     * 描述：成功发送数据后，Socket 监听器将收到该通知
     * @param pSender  事件源对象
     * @param dwConnID 连接 ID
     * @param pData    已发送数据缓冲区
     * @param iLength  已发送数据长度
     * @return HR_OK / HR_IGNORE 继续执行
     *         HR_ERROR          该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
     */
    EnHandleResult OnSend(ITcpClient *pSender, CONNID dwConnID, const BYTE *pData, int iLength) override;

    /**
     * 名称：数据到达通知（PUSH 模型）
     * 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知
     * @param pSender  事件源对象
     * @param dwConnID 连接 ID
     * @param pData    已接收数据缓冲区
     * @param iLength  已接收数据长度
     * @return HR_OK / HR_IGNORE 继续执行
     *         HR_ERROR          引发 OnClose() 事件并关闭连接
     */
    EnHandleResult OnReceive(ITcpClient *pSender, CONNID dwConnID, const BYTE *pData, int iLength) override;

    /**
     * 数据到达通知（PULL 模型）
     * @param pSender
     * @param dwConnID
     * @param iLength
     * @return
     */
    EnHandleResult OnReceive(ITcpClient *pSender, CONNID dwConnID, int iLength) override;

    /**
     * 名称：通信错误通知
     * 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接
     * @param pSender     事件源对象
     * @param dwConnID    连接 ID
     * @param enOperation Socket 操作类型
     * @param iErrorCode  错误代码
     * @return
     */
    EnHandleResult OnClose(ITcpClient *pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) override;

};


#endif //COMMUNICATION_CLIENTLISTENER_H
