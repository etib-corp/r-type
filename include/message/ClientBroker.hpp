#pragma once

#include <cstdint>
#include <string>

#include "message/Broker.hpp"

#include "ResolvingLib.hpp"
#include "interface/INetworkModule/INetworkModule.hpp"
#include "interface/INetworkModule/IServer.hpp"

class ClientBroker : public Broker
{
public:
        ClientBroker(std::string connect_address, std::uint16_t connect_port) : _connect_address(connect_address), _connect_port(connect_port)
    {
        std::string network_module_path = getPathOfNetworkDynLib() + getExtensionKernel();
        std::string core_module_path = "";

        _loader_lib = std::make_unique<LoaderLib>(network_module_path, std::string());

        _loader_lib->LoadModule();

        _network_module = _loader_lib->createNetworkModule();

        _client = _network_module->createClient(_connect_address, _connect_port);

        _client->connectToServer();

        _network_thread = std::thread(&ClientBroker::_run, this);
    }

    ~ClientBroker(void)
    {
    }

    void addMessage(std::uint32_t ecs_id, const std::string &topic_name, std::unique_ptr<Message> message) override;

private:
    std::string _connect_address;
    std::uint16_t _connect_port;
    IClient *_client;

    void _networkRoutine(void) override;

    void _logicalRoutine(void) override;
    
    void _run(void) override;
};
