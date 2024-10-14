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
#include <mutex>

class SessionManager
{
public:
    SessionManager();

    virtual ~SessionManager();

    virtual void addClient(std::shared_ptr<ISession> client);

    virtual std::vector<std::shared_ptr<ISession>> &getClients();

    virtual std::shared_ptr<ISession> getClientById(std::uint32_t id);

    virtual void removeClientById(std::uint32_t id);

    void setOnReceive(std::function<void(const Request &)> onReceive) { _onReceive = onReceive; }

    std::function<void(const Request &)> getOnReceive() { return _onReceive; }

    std::shared_ptr<ISession> popSession(void);

    void pushSession(std::shared_ptr<ISession> session);
protected:
    std::function<void(const Request &)> _onReceive;
    std::mutex _mutex;
    std::vector<std::shared_ptr<ISession>> _sessions;

private:
};

#endif /* !ISESSIONMANAGER_HPP_ */
