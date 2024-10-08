/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"
#include "PackUnpack.hpp"
#include "ECS/Ecs.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "GameClock.hpp"
#include "message/ServerBroker.hpp"
#include "EnumClass.hpp"
#include "Utils.hpp"
#include "ResponsibilityChain.hpp"
#include "Common.hpp"
#include "CallBack.hpp"
#include "SenToAllClient.hpp"
#include <iostream>

static void receiveFromClient(Message *message, ServerBroker *server_broker, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain)
{
    try {
        message = server_broker->getMessage(0, 1);
        if (message == nullptr)
            return;
        std::cout << "Message received from client" << std::endl;
        Header header = {
            .MagicNumber = message->getMagicNumber(),
            .EmmiterdEcsId = message->getEmmiterID(),
            .ReceiverEcsId = message->getReceiverID(),
            .TopicID = message->getTopicID(),
            .Action = message->getAction(),
            .BodyLength = 0
        };
        processHeader(header, _ecs, chain);
        std::cout << "getBody()=" << message->getBody()._buffer << std::endl;
        std::cout << "getReceiverID()=" << (int)message->getReceiverID() << std::endl;
        std::cout << "getEmmiterID()=" << (int)message->getEmmiterID() << std::endl;
        delete message;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cout << "No message received. Waiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

static void receivedFromAllClient(Message *message, ServerBroker *server_broker, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain)
{
    while (true)
    {
        receiveFromClient(message, server_broker, _ecs, chain);
    }
}

int main(void)
{
    GameClock clock;
    ResponsibilityChain chain;
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
    LoaderLib loader_lib(pathLib, "");
    loader_lib.LoadModule();
    Message *message = nullptr;
    INetworkModule *network_module = loader_lib.createNetworkModule();
    ServerBroker *server_broker = new ServerBroker(network_module, 0, 8080);
    auto sessions = server_broker->getClientsSessions();

    attributeServerCallback(&chain, sessions, server_broker, message);

    clock.addCallback([sessions, server_broker, message]()
    {
        std::cout << "All 100 ms : " << std::endl;
        // sendToAllClient(sessions, server_broker, message);
    }, 100);

    clock.addCallback([]()
    {
        std::cout << "Callback B: test 1000 ms" << std::endl;
    }, 1000);

    // clock.start();


    // try {
    //     LoaderLib lb(pathLib, "");
    //     std::ostringstream oss;
    //     Request request;
    //     Header header = {.MagicNumber = 0x21, .ECS_CLIENT_ID = 0x01, .Action = 0x05, .BodyLength = 0x13};
    //     Body body;
    //     _Entity entity = {.type = "Avion[PADING][PADING][PADING][PADING][PADING]", .action = "Voler[PADING][PADING][PADING][PADING][PADING][PADING][PADING]", .life = 3};
    //     ::memmove(&body, &entity, sizeof(_Entity));

    //     showHeader(header);
    //     showBody(reinterpret_cast<_Entity *>(&body));


    //     oss << body;

    //     lb.LoadModule();

    //     INetworkModule *test = lb.createNetworkModule();
    //     IServer *server = test->createServer(8080);

    //     server->run();
    //     while (1) {
    //         if (server->_sessionsManager->_sessions.size() > 0) {
    //             std::shared_ptr<ISession> session = server->_sessionsManager->_sessions[0];
    //             // std::cout << "Sending: " << oss.str() << std::endl;
    //             // request.header = header;
    //             // request.body = body;
    //             ::memset(&request, 0, sizeof(Request));
    //             ::memmove(&request.header, &header, sizeof(Header));
    //             ::memmove(&request.body, oss.str().c_str(), sizeof(Body));
    //             // showHeader(request.header);
    //             // std::cout << "Sending: " << serializeRequest(request)[0] << std::endl;
    //             request.header.BodyLength = oss.str().size();
    //             session->sendTCP(serializeRequest(request));
    //             sleep(5);
    //         }
    //     }
    // }
    // catch(const std::exception& e) {
    //     std::cerr << e.what() << '\n';
    // }
    std::shared_ptr<Ecs> _ecs = std::make_shared<Ecs>();
    Entity entity = _ecs->createEntity();
    _ecs->registerComponent<TransformComponent>();

    _ecs->addComponent<TransformComponent>(entity, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}});

    receivedFromAllClient(message, server_broker, _ecs, chain);

    delete server_broker;
    delete network_module;

    clock.stop();

    return 0;
}
