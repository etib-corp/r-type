/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ServerBroker.cpp
*/

#include "message/ServerBroker.hpp"
#include "ResolvingLib.hpp"

ServerBroker *ServerBroker::_instance = nullptr;
std::mutex ServerBroker::_mutex;

ServerBroker::ServerBroker(void)
{
    std::string networkModulePath = getPathOfNetworkDynLib() + getExtensionKernel();

    _loader_lib = std::make_unique<LoaderLib>(networkModulePath, "");
}

ServerBroker::~ServerBroker(void)
{
}