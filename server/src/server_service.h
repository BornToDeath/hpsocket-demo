//
// Created by lixiaoqing on 2021/7/17.
//

#ifndef HPSOCKET_SERVERSERVICE_H
#define HPSOCKET_SERVERSERVICE_H

#include <memory>

#include "hpsocket/HPSocket.h"

#include "iserver_service.h"

class ServerService final : public IServerService {
public:
    ServerService();

    ~ServerService() override;

public:
    bool Listen(int port) override;

    bool Stop() override;

private:
    std::shared_ptr<CTcpPackServerPtr> server_;
};


#endif //HPSOCKET_SERVERSERVICE_H
