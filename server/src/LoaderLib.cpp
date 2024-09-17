/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LoaderLib
*/

#include "LoaderLib.hpp"

LoaderLib::LoaderLib(const std::string &NetworkModule, const std::string &CoreModule)
{
    this->_pathNetworkModule = NetworkModule;
    this->_pathCoreModule = CoreModule;
    this->_handleNetworkModule = nullptr;
    this->_handleCoreModule = nullptr;
}

LoaderLib::~LoaderLib()
{
}

void LoaderLib::LoadModule(void)
{
    // OPEN_SYM(this->_pathCoreModule, this->_handleCoreModule);
    // if (this->_handleCoreModule == nullptr)
    //     throw LoaderLibError("Can't load the module CORE");

    OPEN_SYM(this->_pathNetworkModule, this->_handleNetworkModule);
    if (this->_handleNetworkModule == nullptr)
        throw LoaderLibError("Can't load the module NETWORK");
    LOAD_SYM(this->_handleNetworkModule, this->_createNetworkModule, "createNetworkModule", INetworkModule*(*)());
}

INetworkModule *LoaderLib::createNetworkModule(void)
{
    return this->_createNetworkModule();
}
