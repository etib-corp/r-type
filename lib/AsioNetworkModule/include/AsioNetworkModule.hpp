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

/**
 * @class AsioNetworkModule
 * @brief A class that implements the INetworkModule interface.
 *
 * The module class provides functionality to run network operations
 * using TCP and UDP connections.
 */
class AsioNetworkModule : public INetworkModule {
    public:
        AsioNetworkModule(int port);
        ~AsioNetworkModule();

        /**
         * @brief Runs the network module.
         *
         * This function waits for a TCP connection and then runs both the TCP and UDP connection handlers.
         */
        void run() override;

    protected:

    private:
};

#endif /* !MODULE_HPP_ */