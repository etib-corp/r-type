/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ISessionManager
*/

#ifndef ISESSIONMANAGER_HPP_
#define ISESSIONMANAGER_HPP_

#include "ISession.hpp"
#include <deque>
#include <memory>

class SessionManager {
    public:
        SessionManager() = default;

        virtual ~SessionManager() = default;


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
    private:
};

#endif /* !ISESSIONMANAGER_HPP_ */
