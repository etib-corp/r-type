#pragma once

#include <cstdint>

#include "message/Broker.hpp"

#include "ResolvingLib.hpp"
#include "LoaderLib.hpp"
#include "interface/INetworkModule/INetworkModule.hpp"

class ServerBroker : public Broker
{
public:
    ServerBroker(std::uint32_t ecs_id, std::uint16_t listen_port) : _listen_port(listen_port)
    {
        setECSId(ecs_id);
        
        std::string network_module_path = getPathOfNetworkDynLib() + getExtensionKernel();
        std::string core_module_path = "";
        
        _loader_lib = std::make_unique<LoaderLib>(network_module_path, std::string());

        _loader_lib->LoadModule();
    }

    ~ServerBroker(void)
    {
    }

    void addMessage(std::uint32_t ecs_id, const std::string &topic_name, std::unique_ptr<Message> message) override;

private:
    std::uint16_t _listen_port;
    std::unique_ptr<LoaderLib> _loader_lib;
};
