#include <iostream>

#include "message/ClientBroker.hpp"

ClientBroker::ClientBroker(INetworkModule *network_module, std::string connect_address, std::uint16_t connect_port) : _connect_address(connect_address), _connect_port(connect_port)
{
    _setNetworkModule(network_module);
    _setSendFunction(std::bind(&ClientBroker::_sendMessage, this, std::placeholders::_1));

    _client = _network_module->createClient(_connect_address, _connect_port);
    std::cout << "ClientBroker network client created" << std::endl;

    _client->connectToServer();
    std::cout << "ClientBroker network client connected" << std::endl;

    _setECSId(_client->getId());

    std::cout << "ClientBroker thread started" << std::endl;
    _thread = std::thread(&ClientBroker::_run, this);
}

ClientBroker::~ClientBroker(void)
{
    std::cout << "ClientBroker is stopping" << std::endl;
    _stop();
    std::cout << "ClientBroker stopped" << std::endl;
}

void ClientBroker::_sendMessage(Message *message)
{
    std::unique_ptr<Request> request = std::move(message->serialize()); 
}
