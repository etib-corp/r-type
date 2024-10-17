/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** SessionManager
*/

#include "interface/INetworkModule/SessionManager.hpp"

SessionManager::SessionManager()
{
}

SessionManager::~SessionManager()
{
}

void SessionManager::addClient(std::shared_ptr<ISession> client)
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::cout << "Session added: " << (int)client->getId() << std::endl;
    _sessions.push_back(client);
}

std::vector<std::shared_ptr<ISession>> &SessionManager::getClients()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _sessions;
}

std::shared_ptr<ISession> SessionManager::getClientById(std::uint32_t id)
{
    std::lock_guard<std::mutex> lock(_mutex);
    for (auto &session : _sessions)
    {
        if (session->getId() == id)
            return session;
    }
    return nullptr;
}

void SessionManager::removeClientById(std::uint32_t id)
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

void SessionManager::setOnReceive(std::function<void(const Request &)> callback)
{
    _onReceive = callback;
}

std::function<void(const Request &)> SessionManager::getOnReceive(void)
{
    return _onReceive;
}

std::shared_ptr<ISession> SessionManager::popSession(void)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_sessions.size() == 0)
        return nullptr;
    auto session = _sessions.front();
    _sessions.erase(_sessions.begin());
    return session;
}

void SessionManager::pushSession(std::shared_ptr<ISession> session)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _sessions.push_back(session);
}
