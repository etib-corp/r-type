/**
 * @file IServer.hpp
 * @brief Interface for the server module in the R-Type project.
 *
 * This file defines the IServer interface, which provides the basic
 * structure for a server in the R-Type project. It includes methods
 * for running the server and setting callbacks for client connections
 * and UDP message reception.
 */

#pragma once

#include <queue>
#include <memory>
#include <iostream>
#include <deque>

#include "interface/INetworkModule/ISession.hpp"
#include "interface/INetworkModule/IListenerTCP.hpp"
#include "interface/INetworkModule/IListenerUDP.hpp"
#include "interface/INetworkModule/SessionManager.hpp"

/**
 * @class IServer
 * @brief Interface for the server module.
 *
 * The IServer class provides an interface for the server module,
 * including methods for running the server and setting callbacks
 * for client connections and UDP message reception.
 */
class IServer
{
public:
    /**
     * @brief Virtual destructor for the IServer interface.
     */

    virtual ~IServer() = default;

    /**
     * @brief Pure virtual function to run the server.
     */
    virtual void run(void) = 0;

    /**
     * @brief Shared pointer to the session manager.
     */

    std::shared_ptr<SessionManager> _sessionsManager;

    /**
     * @brief Sets the callback function for client connections.
     *
     * @param onClientConnected Function to be called when a client connects.
     */
    void setOnClientConnected(std::function<void(ISession *)> onClientConnected) { _listenerTCP->setOnClientConnected(onClientConnected); }

    /**
     * @brief Sets the callback function for receiving UDP messages.
     *
     * @param onReceive Function to be called when a UDP message is received.
     */
    void setOnReceiveUDP(std::function<void(const Request &)> onReceive) { _listenerUDP->setOnReceive(onReceive); }

protected:
    /**
     * @brief Shared pointer to the TCP listener.
     */

    std::shared_ptr<IListenerTCP> _listenerTCP;

    /**
     * @brief Shared pointer to the UDP listener.
     */
    std::shared_ptr<IListenerUDP> _listenerUDP;

private:
};
