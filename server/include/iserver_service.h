//
// Created by lixiaoqing on 2021/7/17.
//

#ifndef SERVER_ISERVER_SERVICE_H
#define SERVER_ISERVER_SERVICE_H

class IServerService {
public:
    virtual ~IServerService() = default;

public:
    static IServerService *GetSingleton();

    static void ReleaseSingleton();

    virtual bool Listen(int port) = 0;

    virtual bool Stop() = 0;
};

#endif //SERVER_ISERVER_SERVICE_H
