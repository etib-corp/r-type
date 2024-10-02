/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IListenerTCP
*/

#ifndef ILISTENERTCP_HPP_
#define ILISTENERTCP_HPP_

#include <queue>
#include <memory>

#include "ISessionManager.hpp"

class IListenerTCP
{
public:
    virtual ~IListenerTCP() = default;

    virtual void WaitForConnection() = 0;

    virtual void run(std::shared_ptr<SessionManager> module) = 0;

protected:
    std::shared_ptr<SessionManager> _sessionManager;

private:
};

#endif /* !ILISTENERTCP_HPP_ */
