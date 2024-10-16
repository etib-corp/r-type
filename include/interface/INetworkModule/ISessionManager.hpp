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
#include "PackUnpack.hpp"
#include <functional>

class SessionManager
{
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

    virtual std::shared_ptr<ISession> getClientById(std::uint32_t id)
    {
        std::deque<std::shared_ptr<ISession>> clients = _sessions;
        while (!clients.empty())
        {
            if (clients.front()->getId() == id)
                return clients.front();
            clients.pop_front();
        }
        return nullptr;
    }

    virtual void removeClientById(std::uint32_t id)
    {
        for (auto it = _sessions.begin(); it != _sessions.end(); it++)
        {
            if ((*it)->getId() == id)
            {
                _sessions.erase(it);
                return;
            }
        }
    }

    void setOnReceive(std::function<void(const Request &)> onReceive) { _onReceive = onReceive; }

    std::function<void(const Request &)> getOnReceive() { return _onReceive; }

    std::deque<std::shared_ptr<ISession>> _sessions;

protected:
    std::function<void(const Request &)> _onReceive;

private:
};

#endif /* !ISESSIONMANAGER_HPP_ */
