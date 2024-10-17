#include <iostream>

#include "message/ServerBroker.hpp"
#include "EnumClass.hpp"
#include "Utils.hpp"
#include "globalLogger.hpp"

ServerBroker::ServerBroker(INetworkModule *network_module, std::uint8_t ecs_id, std::uint16_t listen_port) : _listen_port(listen_port)
{
    _setNetworkModule(network_module);
    _setECSId(ecs_id);
    _setSendFunction(std::bind(&ServerBroker::_sendMessage, this, std::placeholders::_1));

    _server = _network_module->createServer(_listen_port);
    rtypeLog->log("{}", "ServerBroker network server created");


    _server->_sessionsManager->setOnReceive(std::bind(&ServerBroker::_onReceiveRequestCallback, this, std::placeholders::_1));

    _server->setOnReceiveUDP(std::bind(&ServerBroker::_onReceiveRequestCallback, this, std::placeholders::_1));

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
    rtypeLog->log("{}", "ServerBroker is running");


    rtypeLog->log("{}", "ServerBroker thread started");

    _thread = std::thread(&ServerBroker::_run, this);
}

ServerBroker::~ServerBroker(void)
{
    rtypeLog->log("{}", "ServerBroker is stopping");
    _stop();
    rtypeLog->log("{}", "ServerBroker stopped");
}

void ServerBroker::_sendMessage(Message *message)
{
    std::string compressed_request = message->serialize();
    auto client = _server->_sessionsManager->getClientById(message->getReceiverID());

    if (message->isReliable())
        client->sendTCP(compressed_request);
    else
        client->sendUDP(compressed_request);

}

void ServerBroker::_onReceiveRequestCallback(const Request &request)
{
    Message *message = new Message();

    message->setRequest(request);
    _incomming_messages.push(message);
}

void ServerBroker::_onClientDisconnectedCallback(ISession *session)
{
    std::cout << session->getId() << " disconnect" << std::endl;
    rtypeLog->log("{} disconnect", session->getId());
}

void ServerBroker::sendToAllClient(Message *message, std::uint8_t topic_id, std::uint8_t ecs_id)
{
    std::lock_guard<std::mutex> lock(_mutex);

    Message *new_message = nullptr;
    std::vector<std::shared_ptr<ISession>> sessions = _server->_sessionsManager->getClients();

    for (auto &session : sessions)
    {
        new_message = new Message();
        new_message->setRequest(message->getRequest());
        new_message->setReceiverID(session->getId());
        new_message->setEmmiterID(ecs_id);
        new_message->setTopicID(topic_id);
        _outgoing_messages.push(new_message);
    }
}
