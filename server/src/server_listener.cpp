//
// Created by lixiaoqing on 2021/7/17.
//

#include "server_listener.h"

#include "log.h"

#define TAG "ServerListener"

EnHandleResult ServerListener::OnPrepareListen(ITcpServer *pSender, SOCKET soListen) {
    Log::Info(TAG, "OnPrepareListen");
    return HR_OK;
}

EnHandleResult ServerListener::OnAccept(ITcpServer *pSender, CONNID dwConnID, UINT_PTR soClient) {
    Log::Info(TAG, "收到 TCP 连接: %lld", dwConnID);
    return HR_OK;
}

EnHandleResult ServerListener::OnHandShake(ITcpServer *pSender, CONNID dwConnID) {
    Log::Info(TAG, "OnHandShake：%d", dwConnID);
    return HR_OK;
}

EnHandleResult ServerListener::OnReceive(ITcpServer *pSender, CONNID dwConnID, const BYTE *pData, int iLength) {
    return HR_OK;
}

EnHandleResult ServerListener::OnSend(ITcpServer *pSender, CONNID dwConnID, const BYTE *pData, int iLength) {
    Log::Info(TAG, "OnSend：%d, length:%d", dwConnID, iLength);
    return HR_OK;
}

EnHandleResult
ServerListener::OnClose(ITcpServer *pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) {
    Log::Info(TAG, "OnClose:%d", dwConnID);
    return HR_OK;
}

EnHandleResult ServerListener::OnShutdown(ITcpServer *pSender) {
    Log::Info(TAG, "OnShutdown");
    return HR_OK;
}
