/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** AsioNetworkModule
*/

#include "AsioNetworkModule.hpp"

AsioNetworkModule::AsioNetworkModule()
{
}

AsioNetworkModule::~AsioNetworkModule()
{
}

IServer *AsioNetworkModule::createServer(int port)
{
    return new Server(port);
}

IClient *AsioNetworkModule::createClient(const std::string &ip, int port)
{
    return new Client(ip, port);
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

/**
 * @file module.cpp
 * @brief Implementation of the network module creation function.
 *
 * This file contains the implementation of the function to create a new instance
 * of the network module.
 */

extern "C"
{
    /**
     * @brief Creates a new instance of the network module.
     *
     * This function is used to create a new instance of the network module.
     * It returns a pointer to the newly created network module.
     *
     * @return INetworkModule* Pointer to the newly created network module.
     */
    LIBRARY_API INetworkModule *createNetworkModule()
    {
        return new AsioNetworkModule();
    }
}

#else

/**
 * @file module.cpp
 * @brief Implementation of the network module creation function.
 *
 * This file contains the implementation of the function to create a new instance
 * of the network module.
 */

extern "C"
{
    /**
     * @brief Creates a new instance of the network module.
     *
     * This function is used to create a new instance of the network module.
     * It returns a pointer to the newly created network module.
     *
     * @return INetworkModule* Pointer to the newly created network module.
     */
    INetworkModule *createNetworkModule()
    {
        return new AsioNetworkModule();
    }
}

#endif
