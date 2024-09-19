/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ClientBroker.cpp
*/

#include "ClientBroker.hpp"
#include "ResolvingLib.hpp"

ClientBroker *ClientBroker::_instance = nullptr;
std::mutex ClientBroker::_mutex;

ClientBroker::ClientBroker(void)
{
    std::string networkModulePath = getPathOfNetworkDynLib() + getExtensionKernel();

    _loader_lib = std::make_unique<LoaderLib>(networkModulePath, "");
}

ClientBroker::~ClientBroker(void)
{
}
