/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(int port)
{
    _listenerTCP = std::make_shared<ListenerTCP>(port);
    _listenerUDP = std::make_shared<ListenerUDP>(port);
}

Server::~Server()
{
}

void Server::routine()
{
    _listenerTCP->run(this);
    _listenerUDP->run(this);
}