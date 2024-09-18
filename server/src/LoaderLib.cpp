/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LoaderLib
*/

#include "LoaderLib.hpp"

LoaderLib::LoaderLib(const std::string &NetworkModule, const std::string &CoreModule)
{
    _pathNetworkModule = NetworkModule;
    _pathCoreModule = CoreModule;
    _handleNetworkModule = nullptr;
    _handleCoreModule = nullptr;
}

LoaderLib::~LoaderLib()
{
}

void LoaderLib::LoadModule(void)
{
    // OPEN_SYM(_pathCoreModule, _handleCoreModule);
    // if (_handleCoreModule == nullptr)
    //     throw LoaderLibError("Can't load the module CORE");

    OPEN_SYM(_pathNetworkModule, _handleNetworkModule);
    if (_handleNetworkModule == nullptr)
        throw LoaderLibError("Can't load the module NETWORK");
    LOAD_SYM(_handleNetworkModule, _createNetworkModule, "createNetworkModule", INetworkModule*(*)());
}

INetworkModule *LoaderLib::createNetworkModule(void)
{
    return _createNetworkModule();
}
