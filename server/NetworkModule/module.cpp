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
    INetworkModule *createNetworkModule() {
        return new module();
    }
}
