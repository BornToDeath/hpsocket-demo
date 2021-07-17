//
// Created by lixiaoqing on 2021/7/17.
//

#ifndef HPSOCKET_SERVERLISTENER_H
#define HPSOCKET_SERVERLISTENER_H


#include "hpsocket/HPSocket.h"


class ServerListener final : public CTcpServerListener {

public:

    ServerListener() = default;

    ~ServerListener() override = default;

public:

    EnHandleResult OnPrepareListen(ITcpServer *pSender, SOCKET soListen) override;

    EnHandleResult OnAccept(ITcpServer *pSender, CONNID dwConnID, UINT_PTR soClient) override;

    EnHandleResult OnHandShake(ITcpServer *pSender, CONNID dwConnID) override;

    EnHandleResult OnReceive(ITcpServer *pSender, CONNID dwConnID, const BYTE *pData, int iLength) override;

    EnHandleResult OnSend(ITcpServer *pSender, CONNID dwConnID, const BYTE *pData, int iLength) override;

    EnHandleResult
    OnClose(ITcpServer *pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) override;

    EnHandleResult OnShutdown(ITcpServer *pSender) override;

};

#endif //HPSOCKET_SERVERLISTENER_H
