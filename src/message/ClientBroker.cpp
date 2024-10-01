#include <iostream>

#include "message/ClientBroker.hpp"

ClientBroker::ClientBroker(std::string connect_address, std::uint16_t connect_port) : _connect_address(connect_address), _connect_port(connect_port)
{
    std::string network_module_path = getPathOfNetworkDynLib() + getExtensionKernel();
    std::string core_module_path = "";

    _loader_lib = std::make_unique<LoaderLib>(network_module_path, std::string());

    _loader_lib->LoadModule();

    _network_module = _loader_lib->createNetworkModule();

    _client = _network_module->createClient(_connect_address, _connect_port);

    _client->connectToServer();

    _thread = std::thread(&ClientBroker::_run, this);
}

ClientBroker::~ClientBroker(void)
{
    _mutex.lock();
    _is_running = false;
    _mutex.unlock();
    _thread.join();
}

void ClientBroker::_networkRoutine(void)
{
    std::cout << "ClientBroker networkRoutine" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}


