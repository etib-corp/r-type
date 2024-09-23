/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IServer
*/

#ifndef ISERVER_HPP_
#define ISERVER_HPP_

#include <queue>
#include <memory>
#include <iostream>
#include <deque>

#include "interface/INetworkModule/IListenerTCP.hpp"
#include "interface/INetworkModule/IListenerUDP.hpp"
#include "interface/INetworkModule/ISession.hpp"

class IServer {
    public:
        virtual ~IServer() = default;

        virtual void routine(void) = 0;

        virtual void addClient(std::shared_ptr<ISession> client)
        {
            _sessions.push_back(client);
        }

        virtual std::deque<std::shared_ptr<ISession>> &getClients()
        {
            return _sessions;
        }

        virtual std::shared_ptr<ISession> getClientById(int id)
        {
            std::deque<std::shared_ptr<ISession>> clients = _sessions;
            while (!clients.empty()) {
                if (clients.front()->getId() == id)
                    return clients.front();
                clients.pop_front();
            }
            return nullptr;
        }

        virtual void removeClientById(int id)
        {
            for (auto it = _sessions.begin(); it != _sessions.end(); it++) {
                if ((*it)->getId() == id) {
                    _sessions.erase(it);
                    return;
                }
            }
        }

        std::deque<std::shared_ptr<ISession>> _sessions;

    protected:

        std::shared_ptr<IListenerTCP> _listenerTCP;
        std::shared_ptr<IListenerUDP> _listenerUDP;
    private:
};

#endif /* !ISERVER_HPP_ */
