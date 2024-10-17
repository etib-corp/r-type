/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(int port)
{
    _listenerTCP = std::make_unique<ListenerTCP>(port);
    _listenerUDP = std::make_unique<ListenerUDP>(port + 1);
    _sessionsManager = std::make_shared<SessionManager>();
}

Server::~Server()
{
}

void Server::run(void)
{
    _listenerTCP->run(_sessionsManager);
    _listenerUDP->run(_sessionsManager);
}
