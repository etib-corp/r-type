/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** module
*/

#ifndef MODULE_HPP_
#define MODULE_HPP_

#include "interface/INetworkModule/INetworkModule.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include "ListenerTCP.hpp"
#include <memory>
#include "ListenerUDP.hpp"
#include "Client.hpp"
#include "Server.hpp"

/**
 * @class AsioNetworkModule
 * @brief A class that implements the INetworkModule interface.
 *
 * The module class provides functionality to run network operations
 * using TCP and UDP connections.
 */
class AsioNetworkModule : public INetworkModule {
    public:
        AsioNetworkModule();
        ~AsioNetworkModule();

        IServer *createServer(int port) override;

        IClient *createClient(const std::string& ip, int port) override;

    protected:

    private:
};

#endif /* !MODULE_HPP_ */
