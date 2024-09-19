/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ANetworkModule
*/

#ifndef ANETWORKMODULE_HPP_
#define ANETWORKMODULE_HPP_

#include "interface/IListenerTCP.hpp"
#include <queue>
#include <memory>
#include "interface/IListenerUDP.hpp"
#include "interface/ISession.hpp"
#include <iostream>

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

        virtual void run() = 0;

        virtual void addClient(std::shared_ptr<ISession> client)
        {
            _sessions.push(client);
        }

        virtual std::queue<std::shared_ptr<ISession>> &getClients()
        {
            return _sessions;
        }

        virtual std::shared_ptr<ISession> getClientById(int id)
        {
            std::queue<std::shared_ptr<ISession>> clients = _sessions;
            while (!clients.empty()) {
                if (clients.front()->getId() == id)
                    return clients.front();
                clients.pop();
            }
            return nullptr;
        }

        /**
         * @brief A queue that holds shared pointers to IClient sessions.
         *
         * This queue is used to manage and store client sessions in a
         * thread-safe manner. Each session is represented by a shared
         * pointer to an IClient object, ensuring proper memory management
         * and reference counting.
         */
        std::queue<std::shared_ptr<ISession>> _sessions;
    protected:

         /**
         * @brief A shared pointer to a ConnectionTCP object.
         *
         * This member variable holds a shared pointer to an instance of the ConnectionTCP class,
         * which manages a TCP connection. The use of std::shared_ptr ensures that the
         * ConnectionTCP object is properly managed and deallocated when no longer in use.
         */
        std::shared_ptr<IListenerTCP> _listenerTCP;

        /**
         * @brief A shared pointer to a ConnectionUDP object.
         *
         * This member variable holds a shared pointer to an instance of the ConnectionUDP class,
         * which is used to manage UDP connections within the network module.
         */
        std::shared_ptr<IListenerUDP> _listenerUDP;
    private:
};

#endif /* !ANETWORKMODULE_HPP_ */
