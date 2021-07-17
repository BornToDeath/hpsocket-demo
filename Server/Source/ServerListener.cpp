//
// Created by lixiaoqing on 2021/7/17.
//


#include "ServerListener.h"
#include "Log.h"

#define TAG "ServerListener"


EnHandleResult ServerListener::OnPrepareListen(ITcpServer *pSender, SOCKET soListen) {
    Log::info(TAG, "OnPrepareListen");
    return HR_OK;
}

EnHandleResult ServerListener::OnAccept(ITcpServer *pSender, CONNID dwConnID, UINT_PTR soClient) {
    Log::info(TAG, "收到 TCP 连接: %lld", dwConnID);
    return HR_OK;
}

EnHandleResult ServerListener::OnHandShake(ITcpServer *pSender, CONNID dwConnID) {
    Log::info(TAG, "OnHandShake：%d", dwConnID);
    return HR_OK;
}

EnHandleResult ServerListener::OnReceive(ITcpServer *pSender, CONNID dwConnID, const BYTE *pData, int iLength) {
    return HR_OK;
}

EnHandleResult ServerListener::OnSend(ITcpServer *pSender, CONNID dwConnID, const BYTE *pData, int iLength) {
    Log::info(TAG, "OnSend：%d, length:%d", dwConnID, iLength);
    return HR_OK;
}

EnHandleResult
ServerListener::OnClose(ITcpServer *pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) {
    Log::info(TAG, "OnClose:%d", dwConnID);
    return HR_OK;
}

EnHandleResult ServerListener::OnShutdown(ITcpServer *pSender) {
    Log::info(TAG, "OnShutdown");
    return HR_OK;
}
