#pragma once

#include <cstdint>

#include "message/Broker.hpp"

#include "ResolvingLib.hpp"
#include "interface/INetworkModule/INetworkModule.hpp"
#include "interface/INetworkModule/IServer.hpp"

class ServerBroker : public Broker
{
public:
    ServerBroker(std::uint32_t ecs_id, std::uint16_t listen_port);

    ~ServerBroker(void);

private:
    std::uint16_t _listen_port;
    IServer *_server;

    void _networkRoutine(void) override;
};
