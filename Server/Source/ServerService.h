//
// Created by lixiaoqing on 2021/7/17.
//

#ifndef HPSOCKET_SERVERSERVICE_H
#define HPSOCKET_SERVERSERVICE_H


#include "IServerService.h"


class ServerService final : public IServerService {

public:

    ServerService() = default;

    ~ServerService() override = default;

    void listen(int port) override;

};


#endif //HPSOCKET_SERVERSERVICE_H
