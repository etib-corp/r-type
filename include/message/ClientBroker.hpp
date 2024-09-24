#pragma once

#include <cstdint>
#include <string>

#include "message/Broker.hpp"

#include "ResolvingLib.hpp"
#include "interface/INetworkModule/INetworkModule.hpp"
#include "interface/INetworkModule/IServer.hpp"

class ClientBroker : public Broker
{
public:
    ClientBroker(std::string connect_address, std::uint16_t connect_port);

    ~ClientBroker(void);

private:
    std::string _connect_address;
    std::uint16_t _connect_port;
    IClient *_client;

    void _networkRoutine(void) override;
};
