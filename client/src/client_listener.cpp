//
// Created by lixiaoqing on 2021/5/27.
//

#include "client_listener.h"

#include <cstring>

#include "log.h"

#define TAG "ClientListener"

ClientListener::~ClientListener() {
    Log::Info(TAG, "【析构】%s", __PRETTY_FUNCTION__);
}


EnHandleResult ClientListener::OnPrepareConnect(ITcpClient *pSender, CONNID dwConnID, SOCKET socket) {
    return HR_OK;
}

EnHandleResult ClientListener::OnConnect(ITcpClient *pSender, CONNID dwConnID) {
    Log::Info(TAG, "%s", __PRETTY_FUNCTION__);
    return HR_OK;
}

EnHandleResult ClientListener::OnHandShake(ITcpClient *pSender, CONNID dwConnID) {
    return HR_OK;
}

EnHandleResult ClientListener::OnReceive(ITcpClient *pSender, CONNID dwConnID, const BYTE *pData, int iLength) {

    Log::Info(TAG, "【接收】数据长度: %d", iLength);
    return HR_OK;
}

EnHandleResult ClientListener::OnReceive(ITcpClient *pSender, CONNID dwConnID, int iLength) {
    return HR_OK;
}

EnHandleResult ClientListener::OnSend(ITcpClient *pSender, CONNID dwConnID, const BYTE *pData, int iLength) {
    return HR_OK;
}

EnHandleResult
ClientListener::OnClose(ITcpClient *pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) {
    Log::Warn(TAG, "Socket 连接中断!");
    return HR_OK;
}