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
#include <cstdint>

#include "SessionManager.hpp"

class IListenerTCP
{
public:
    virtual ~IListenerTCP() = default;

    virtual void WaitForConnection() = 0;

    virtual void run(std::shared_ptr<SessionManager> module) = 0;

    void setOnClientConnected(std::function<void(ISession *)> onClientConnected) { _onClientConnected = onClientConnected; }

protected:

    std::function<void(ISession *)> _onClientConnected = nullptr;

    std::shared_ptr<SessionManager> _sessionManager;

    std::uint8_t _last_id = 0;

private:
};

#endif /* !ILISTENERTCP_HPP_ */
