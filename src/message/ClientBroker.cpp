/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ClientBroker
*/

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

    _client->setOnReceive(std::bind(&ClientBroker::_onReceiveRequestCallback, this, std::placeholders::_1));

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
    std::string compressed_request = message->serialize();

    if (message->isReliable())
        _client->sendTCP(compressed_request);
    else
        _client->sendUDP(compressed_request);
}

void ClientBroker::_onReceiveRequestCallback(const Request &request)
{
    static bool first_message = false;
    Message *message = nullptr;

    if (!first_message) {
        std::cout << "ClientBroker received first message" << std::endl;
        first_message = true;
        _client->setId(request.header.ReceiverEcsId);
        _setECSId(request.header.ReceiverEcsId);
        std::cout << "ClientBroker ID set to " << (int)_ecs_id << std::endl;
        return;
    }
    message = new Message();

    message->setRequest(request);
    _incomming_messages.push(message);
}
