//
// Created by lixiaoqing on 2021/7/17.
//

#ifndef HPSOCKET_ISERVERSERVICE_H
#define HPSOCKET_ISERVERSERVICE_H


class IServerService {

public:

    virtual ~IServerService() = default;

    static IServerService *getSingleton();

    static void releaseSingleton();

    virtual void listen(int port) = 0;

};


#endif //HPSOCKET_ISERVERSERVICE_H
