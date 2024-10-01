/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IServer
*/

#pragma once

#include <queue>
#include <memory>
#include <iostream>
#include <deque>

#include "interface/INetworkModule/ISession.hpp"
#include "interface/INetworkModule/IListenerTCP.hpp"
#include "interface/INetworkModule/IListenerUDP.hpp"
#include "interface/INetworkModule/ISessionManager.hpp"

class IServer
{
public:
    virtual ~IServer() = default;

    virtual void run(void) = 0;

    std::shared_ptr<SessionManager> _sessionsManager;

protected:
    std::shared_ptr<IListenerTCP> _listenerTCP;
    std::shared_ptr<IListenerUDP> _listenerUDP;

private:
};
