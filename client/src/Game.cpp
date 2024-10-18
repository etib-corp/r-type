/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Game
*/

#include "Game.hpp"

static void receiveFromServer(ClientBroker *client_broker, std::shared_ptr<Ecs> _ecs, ResponsibilityChain& chain)
{
    try {
        Message *message = nullptr;
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
        // std::cerr << e.what() << std::endl;
        // std::cout << "No message received. Waiting..." << std::endl;
    }
}

LE::Game::Game()
{
    std::cout << "Game constructor" << std::endl;
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
    LoaderLib loaderLib(pathLib, "");

    loaderLib.LoadModule();
    _networkModule = loaderLib.createNetworkModule();
    _clientBroker = new ClientBroker(_networkModule, "10.49.84.132", 8080);
    _responsibilityChain = ResponsibilityChain();
    _sceneManager = std::make_shared<SceneManager>();
}

LE::Game::~Game()
{
    delete _clientBroker;
    delete _networkModule;
}

bool LE::Game::init()
{
    std::cout << "Game init" << std::endl;
    return true;
}

void LE::Game::addScene(const std::string &name, const std::shared_ptr<Scene> &scene)
{
    scene->setClientBroker(_clientBroker);
    _sceneManager->addScene(scene, name);
}

void LE::Game::update()
{
    receiveFromServer(_clientBroker, _sceneManager->getCurrentScene()->_ecs, _responsibilityChain);
}
