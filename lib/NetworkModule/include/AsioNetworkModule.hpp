/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** module
*/

#pragma once

#include "interface/INetworkModule/INetworkModule.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include "ListenerTCP.hpp"
#include <memory>
#include "ListenerUDP.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "dllDefine.hpp"

/**
 * @class AsioNetworkModule
 * @brief A class that implements the INetworkModule interface.
 *
 * The module class provides functionality to run network operations
 * using TCP and UDP connections.
 */
class LIBRARY_API AsioNetworkModule : public INetworkModule {
    public:
        AsioNetworkModule();
        ~AsioNetworkModule();

        IServer *createServer(int port) override;

        IClient *createClient(const std::string& ip, int port) override;

    protected:

    private:
};
