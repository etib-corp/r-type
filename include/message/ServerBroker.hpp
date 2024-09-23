#pragma once

#include <cstdint>

#include "message/Broker.hpp"

#include "ResolvingLib.hpp"
#include "LoaderLib.hpp"
#include "interface/INetworkModule/INetworkModule.hpp"
#include "interface/INetworkModule/IServer.hpp"

class ServerBroker : public Broker
{
public:
    ServerBroker(std::uint32_t ecs_id, std::uint16_t listen_port) : _listen_port(listen_port)
    {
        setECSId(ecs_id);
        
        std::string network_module_path = getPathOfNetworkDynLib() + getExtensionKernel();
        std::string core_module_path = "";
        
        _loader_lib = std::make_unique<LoaderLib>(network_module_path, core_module_path);

        _loader_lib->LoadModule();

        _network_module = _loader_lib->createNetworkModule();

        _server = _network_module->createServer(_listen_port);

        _network_thread = std::thread(&ServerBroker::_run, this);
    }

    ~ServerBroker(void)
    {
    }

    void addMessage(std::uint32_t ecs_id, const std::string &topic_name, std::unique_ptr<Message> message) override;

private:
    std::uint16_t _listen_port;
    IServer *_server;

    void _networkRoutine(void) override;

    void _logicalRoutine(void) override;

    void _run(void) override;
};
