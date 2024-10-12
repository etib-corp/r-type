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
#include "CallbackServer.hpp"
#include <iostream>
#include "globalLogger.hpp"
#include "fmt/core.h"

static void receiveFromClient(ServerBroker *server_broker, std::shared_ptr<ISession> session, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain)
{
    try {
        Message *message = nullptr;
        message = server_broker->getMessage(session->getId(), 1);
        if (message == nullptr) {
            return;
        }
        Request req = message->getRequest();
        processRequest(req, _ecs, chain);
        // delete message;
    } catch (const std::exception &e) {
    }
}

static void receivedFromAllClient(ServerBroker *server_broker, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain)
{
    while (true)
    {
        for (auto session : server_broker->getClientsSessions())
        {
            receiveFromClient(server_broker, session, _ecs, chain);
        }
    }
}

int main(void)
{
    rtypeLog->log("Server started");
    GameClock clock;
    ResponsibilityChain chain;
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
    LoaderLib loader_lib(pathLib, "");
    loader_lib.LoadModule();
    INetworkModule *network_module = loader_lib.createNetworkModule();
    ServerBroker *server_broker = new ServerBroker(network_module, 0, 8080);

    attributeServerCallback(&chain, server_broker);

    int nbrPlayer = 0;
    chain.addActionCallback(asChar(ActionCode::READY), [&nbrPlayer, &server_broker](const Request &req, std::shared_ptr<Ecs> _ecs) {
        nbrPlayer++;
        if (nbrPlayer != 2) {
            return;
        }
        Request request = {
            .header = {
                .MagicNumber = 0xFF,
                .EmmiterdEcsId = 0x00,
                .ReceiverEcsId = request.header.EmmiterdEcsId,
                .TopicID = 0x00,
                .Action = asChar(ActionCode::START_GAME),
                .BodyLength = 0},
            .body = {0}};
        StartGame startGame;
        startGame.nbrPlayers = nbrPlayer;
        ::memmove(request.body._buffer, &startGame, sizeof(StartGame));
        Message msg;
        msg.setRequest(request);
        msg.setReliable(true);
        server_broker->sendToAllClient(&msg, 1);
    });


    std::shared_ptr<Ecs> _ecs = std::make_shared<Ecs>();
    Entity entity = _ecs->createEntity();
    _ecs->registerComponent<TransformComponent>();

    _ecs->addComponent<TransformComponent>(entity, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}});

    receivedFromAllClient(server_broker, _ecs, chain);

    delete server_broker;
    delete network_module;
    return 0;
}
