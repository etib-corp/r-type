/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ANetworkModule
*/

#ifndef ANETWORKMODULE_HPP_
#define ANETWORKMODULE_HPP_

#include <queue>
#include <memory>
#include <iostream>

#include "interface/INetworkModule/IListenerTCP.hpp"
#include "interface/INetworkModule/IListenerUDP.hpp"
#include "interface/INetworkModule/ISession.hpp"
#include "interface/INetworkModule/IClient.hpp"
#include "interface/INetworkModule/IServer.hpp"

/**
 * @class INetworkModule
 * @brief Abstract base class for network modules.
 *
 * This class defines the interface for network modules, providing a pure virtual
 * function `run` that must be implemented by derived classes. It also includes
 * a virtual destructor to ensure proper cleanup of derived classes.
 */
class INetworkModule {
    public:
        virtual ~INetworkModule() = default;

        /**
         * @brief Runs a server IServer
         *
         * This pure virtual function must be implemented by derived classes to run the server.
         * It is used to start the server and begin listening for incoming connections.
         */
        virtual IServer *createServer(int port) = 0;

        virtual IClient *createClient(const std::string& ip, int port) = 0;

    protected:

    private:
};

#endif /* !ANETWORKMODULE_HPP_ */
