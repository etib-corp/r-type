#pragma once

#include <cstdint>
#include <string>

#include "message/Broker.hpp"

#include "ResolvingLib.hpp"
#include "LoaderLib.hpp"


class ClientBroker : public Broker
{
public:
    ClientBroker(std::uint32_t ecs_id, std::string connect_address, std::uint16_t connect_port) : _connect_address(connect_address), _connect_port(connect_port)
    {
        setECSId(ecs_id);

        std::string network_module_path = getPathOfNetworkDynLib() + getExtensionKernel();
        std::string core_module_path = "";
        
        _loader_lib = std::make_unique<LoaderLib>(network_module_path, std::string());

        _loader_lib->LoadModule();
    }

    ~ClientBroker(void)
    {
    }

    void addMessage(std::uint32_t ecs_id, const std::string &topic_name, std::unique_ptr<Message> message) override;

private:
    std::string _connect_address;
    std::uint16_t _connect_port;
    std::unique_ptr<LoaderLib> _loader_lib;
};
