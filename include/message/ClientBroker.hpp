#pragma once

#include <cstdint>
#include <string>

#include "message/Broker.hpp"

#include "ResolvingLib.hpp"

#include "interface/INetworkModule/INetworkModule.hpp"
#include "interface/INetworkModule/IServer.hpp"

/**
 * @class ClientBroker
 * @brief A class that handles client-side network communication.
 *
 * ClientBroker is responsible for connecting to a server and managing the network routine
 * for client-side operations. It inherits from the Broker class.
 */
class ClientBroker : public Broker
{
public:
    /**
     * @brief Constructs a new ClientBroker object.
     *
     * @param connect_address The address to connect to.
     * @param connect_port The port to connect to.
     */
    ClientBroker(std::string connect_address, std::uint16_t connect_port);

    /**
     * @brief Destroys the ClientBroker object.
     */

    ~ClientBroker(void);

private:
    std::string _connect_address;
    std::uint16_t _connect_port;
    IClient *_client;

    void _networkRoutine(void) override;
};
