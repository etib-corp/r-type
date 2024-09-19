/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ServerBroker.cpp
*/

#include "ServerBroker.hpp"
#include "ResolvingLib.hpp"
#include "module.hpp"

ServerBroker *ServerBroker::_instance = nullptr;
std::mutex ServerBroker::_mutex;

ServerBroker::ServerBroker(void)
{
    std::string networkModulePath = getPathOfNetworkDynLib() + getExtensionKernel();

    _loader_lib = std::make_unique<LoaderLib>(networkModulePath, "");

    _network_module = std::make_unique<module>(_loader_lib->createNetworkModule(LISTEN_PORT));
}

ServerBroker::~ServerBroker(void)
{
}