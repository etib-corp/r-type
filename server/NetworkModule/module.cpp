/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** module
*/

#include "module.hpp"

module::module()
{
    _connectionTCP = std::make_shared<ConnectionTCP>(8080);
    _connectionUDP = std::make_shared<ConnectionUDP>(8081);
}

module::~module()
{
}

void module::run()
{
    _connectionTCP->WaitForConnection();
    _connectionTCP->run();
    _connectionUDP->run();
}

extern "C" {
    INetworkModule *createNetworkModule()
    {
        return new module();
    }
}
