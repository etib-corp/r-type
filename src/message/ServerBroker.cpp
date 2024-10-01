#include <iostream>

#include "message/ServerBroker.hpp"

ServerBroker::ServerBroker(INetworkModule *network_module, std::uint32_t ecs_id, std::uint16_t listen_port) : _listen_port(listen_port)
{
    _setNetworkModule(network_module);
    _setECSId(ecs_id);
    _setSendFunction(std::bind(&ServerBroker::_sendMessage, this, std::placeholders::_1));

    _server = _network_module->createServer(_listen_port);
    std::cout << "ServerBroker network server created" << std::endl;

    _server->run();
    std::cout << "ServerBroker is running" << std::endl;

    std::cout << "ServerBroker thread started" << std::endl;
    _thread = std::thread(&ServerBroker::_run, this);
}

ServerBroker::~ServerBroker(void)
{
    std::cout << "ServerBroker is stopping" << std::endl;
    _stop();
    std::cout << "ServerBroker stopped" << std::endl;
}

void ServerBroker::_sendMessage(Message *message)
{
    std::unique_ptr<Request> request = std::move(message->serialize());
}
