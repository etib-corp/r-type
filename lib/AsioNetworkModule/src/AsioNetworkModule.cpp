/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** AsioNetworkModule
*/

#include "AsioNetworkModule.hpp"

AsioNetworkModule::AsioNetworkModule(int port)
{
    _listenerTCP = std::make_shared<ListenerTCP>(port);
    _listenerUDP = std::make_shared<ListenerUDP>(port);
}

AsioNetworkModule::~AsioNetworkModule()
{
}

void AsioNetworkModule::run()
{
    _listenerTCP->run(this);
    _listenerUDP->run(this);
}

/**
 * @file module.cpp
 * @brief Implementation of the network module creation function.
 *
 * This file contains the implementation of the function to create a new instance
 * of the network module.
 */

extern "C" {
    /**
     * @brief Creates a new instance of the network module.
     *
     * This function is used to create a new instance of the network module.
     * It returns a pointer to the newly created network module.
     *
     * @return INetworkModule* Pointer to the newly created network module.
     */
    INetworkModule *createAsioNetworkModule(int port) {
        return new AsioNetworkModule(port);
    }
}
