/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** module
*/

#ifndef MODULE_HPP_
#define MODULE_HPP_

#include "interface/INetworkModule.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include "ConnectionTCP.hpp"
#include <memory>
#include "ConnectionUDP.hpp"
#include "ConnectionUDP.hpp"

/**
 * @class module
 * @brief A class that implements the INetworkModule interface.
 *
 * The module class provides functionality to run network operations
 * using TCP and UDP connections.
 */
class module : public INetworkModule {
    public:
        module();
        ~module();

        /**
         * @brief Runs the network module.
         *
         * This function waits for a TCP connection and then runs both the TCP and UDP connection handlers.
         */
        void run() override;

    protected:
        /**
         * @brief A shared pointer to a ConnectionTCP object.
         *
         * This member variable holds a shared pointer to an instance of the ConnectionTCP class,
         * which manages a TCP connection. The use of std::shared_ptr ensures that the
         * ConnectionTCP object is properly managed and deallocated when no longer in use.
         */
        std::shared_ptr<ConnectionTCP> _connectionTCP;

        /**
         * @brief A shared pointer to a ConnectionUDP object.
         *
         * This member variable holds a shared pointer to an instance of the ConnectionUDP class,
         * which is used to manage UDP connections within the network module.
         */
        std::shared_ptr<ConnectionUDP> _connectionUDP;
    private:
};

#endif /* !MODULE_HPP_ */
