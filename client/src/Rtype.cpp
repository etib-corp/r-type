/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Rtype
*/

#include "Rtype.hpp"

static void processRequest(const Request& req, std::shared_ptr<LE::Ecs> _ecs, std::shared_ptr<LE::ResponsibilityChain> chain)
{
    auto callbacks = chain->getActionCallbacks(req.header.Action);
    bool callbackState = false;

    for (const auto& callback : callbacks)
    {
        callbackState =  callback(req, _ecs);
        if (!callbackState)
        {
            break;
        }
    }
}

static void receiveFromServer(std::shared_ptr<LE::ClientBroker> client_broker, std::shared_ptr<LE::Ecs> _ecs, std::shared_ptr<LE::ResponsibilityChain> chain)
{
    try {
        std::shared_ptr<LE::Message> message = nullptr;
        message = client_broker->getMessageFromTopic(1);
        if (message == nullptr)
            return;
        std::cout << "Message received from server" << std::endl;
        Request req = message->getRequest();
        processRequest(req, _ecs, chain);
        std::cout << "getBody()=" << message->getBody()._buffer << std::endl;
        std::cout << "getReceiverID()=" << (int)message->getReceiverID() << std::endl;
        std::cout << "getEmmiterID()=" << (int)message->getEmmiterID() << std::endl;
        // delete message;
    } catch (const std::exception &e) {
    }
}

Rtype::Rtype()
{
}

Rtype::~Rtype()
{
}

void Rtype::init(LE::IEngine& engine)
{
    _sceneManager = engine.createSceneManager();
    _responsibilityChain = std::make_shared<LE::ResponsibilityChain>();
    _clientBroker = std::make_shared<LE::ClientBroker>(engine.getNetworkModule(), "127.0.0.1", 8080);

    attributeClientCallback(_responsibilityChain, _clientBroker);
}

void Rtype::update()
{
    if (_clientBroker)
        receiveFromServer(_clientBroker, _sceneManager->getCurrentScene()->getEcs(), _responsibilityChain);
}
