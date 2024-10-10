#include <iostream>

#include "message/ServerBroker.hpp"
#include "EnumClass.hpp"
#include "Utils.hpp"

ServerBroker::ServerBroker(INetworkModule *network_module, std::uint8_t ecs_id, std::uint16_t listen_port) : _listen_port(listen_port)
{
    _setNetworkModule(network_module);
    _setECSId(ecs_id);
    _setSendFunction(std::bind(&ServerBroker::_sendMessage, this, std::placeholders::_1));

    _server = _network_module->createServer(_listen_port);
    std::cout << "ServerBroker network server created" << std::endl;

    _server->_sessionsManager->setOnReceive(std::bind(&ServerBroker::_onReceiveRequestCallback, this, std::placeholders::_1));

    _server->setOnClientConnected([](ISession *session) {
        Request request = {
            .header = {
                .MagicNumber = 0xFF,
                .EmmiterdEcsId = 00,
                .ReceiverEcsId = session->getId(),
                .TopicID = 0x00,
                .Action = asChar(ActionCode::NEW_CONNECTION),
                .BodyLength = 0
            },
            .body = {0}
        };
        
        Message *message = new Message();

        message->setHeader(request.header);
        message->setBody(request.body);
        std::string compress_message = message->serialize();
        session->sendTCP(compress_message);
        delete message;
    });

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
    std::string compress_request = message->serialize();

    _server->_sessionsManager->getClientById(message->getReceiverID())->sendTCP(compress_request);
}

void ServerBroker::_onReceiveRequestCallback(const Request &request)
{
    Message *message = new Message();
    
    _incomming_messages.push(message);
}

void ServerBroker::_onClientDisconnectedCallback(ISession *session)
{
    std::cout << session->getId() << " disconnect" << std::endl;
}
