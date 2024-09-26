#pragma once

#include <cstdint>

#include "message/Broker.hpp"

#include "ResolvingLib.hpp"
#include "interface/INetworkModule/INetworkModule.hpp"
#include "interface/INetworkModule/IServer.hpp"

/**
 * @class ServerBroker
 * @brief A class that extends Broker to manage server-side network communication.
 *
 * The ServerBroker class is responsible for handling network operations on the server side.
 * It listens on a specified port and manages network routines.
 */
class ServerBroker : public Broker
{
public:
    /**
     * @brief Constructs a new ServerBroker object.
     *
     * @param ecs_id The ID of the ECS (Entity Component System).
     * @param listen_port The port on which the server will listen for incoming connections.
     */
    ServerBroker(std::uint32_t ecs_id, std::uint16_t listen_port);

    /**
     * @brief Destroys the ServerBroker object.
     */
    ~ServerBroker(void);

private:
    std::uint16_t _listen_port;
    IServer *_server;

    void _networkRoutine(void) override;
};
