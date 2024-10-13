/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ISessionManager
*/

#ifndef ISESSIONMANAGER_HPP_
#define ISESSIONMANAGER_HPP_

#include "ISession.hpp"
#include <vector>
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
        std::lock_guard<std::mutex> lock(_mutex);
        std::cout << "Session added: " << (int)client->getId() << std::endl;
        _sessions.push_back(client);
    }

    virtual std::vector<std::shared_ptr<ISession>> &getClients()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _sessions;
    }

    virtual std::shared_ptr<ISession> getClientById(std::uint32_t id)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        for (auto &session : _sessions)
        {
            if (session->getId() == id)
                return session;
        }
        return nullptr;
    }

    virtual void removeClientById(std::uint32_t id)
    {
        std::lock_guard<std::mutex> lock(_mutex);
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

    std::shared_ptr<ISession> popSession(void)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_sessions.size() == 0)
            return nullptr;
        auto session = _sessions.front();
        _sessions.erase(_sessions.begin());
        return session;
    }

    void pushSession(std::shared_ptr<ISession> session)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _sessions.push_back(session);
    }

    std::vector<std::shared_ptr<ISession>> _sessions;

protected:
    std::function<void(const Request &)> _onReceive;
    std::mutex _mutex;

private:
};

#endif /* !ISESSIONMANAGER_HPP_ */
