/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LoaderLib
*/

#include "LoaderLib.hpp"
#include "globalLogger.hpp"

LoaderLib::LoaderLib(const std::string &NetworkModule, const std::string &CoreModule)
{
    _pathNetworkModule = NetworkModule;
    _pathCoreModule = CoreModule;
    _handleNetworkModule = nullptr;
    _handleCoreModule = nullptr;
    _createNetworkModule = nullptr;
}

LoaderLib::~LoaderLib()
{
    if (_handleNetworkModule) {
        CLOSE_SYM(_handleNetworkModule);
    }
    
    if (_handleCoreModule) {
        CLOSE_SYM(_handleCoreModule);
    }
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
    if (_createNetworkModule == nullptr)
        throw LoaderLibError("Can't load the symbol createNetworkModule");
}

INetworkModule *LoaderLib::createNetworkModule(void)
{
    if (_createNetworkModule == nullptr)
        throw LoaderLibError("createNetworkModule is not loaded");

    return _createNetworkModule();
}

// ICoreModule *LoaderLib::createCoreModule(void)
// {
//     if (_createCoreModule == nullptr)
//         throw LoaderLibError("createCoreModule is not loaded");
//     return _createCoreModule();
// }
