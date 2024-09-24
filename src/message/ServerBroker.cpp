#include <iostream>

#include "message/ServerBroker.hpp"

ServerBroker::ServerBroker(std::uint32_t ecs_id, std::uint16_t listen_port) : _listen_port(listen_port)
{
    setECSId(ecs_id);

    std::string network_module_path = getPathOfNetworkDynLib() + getExtensionKernel();
    std::string core_module_path = "";

    _loader_lib = std::make_unique<LoaderLib>(network_module_path, core_module_path);

    _loader_lib->LoadModule();

    _network_module = _loader_lib->createNetworkModule();

    _server = _network_module->createServer(_listen_port);

    _thread = std::thread(&ServerBroker::_run, this);
}

ServerBroker::~ServerBroker(void)
{
    _is_running = false;
    _thread.join();
}

void ServerBroker::_networkRoutine(void)
{
    std::cout << "ServerBroker networkRoutine" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
