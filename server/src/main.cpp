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
#include "ECS/Systems/MoveSystem.hpp"
#include <chrono>

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
    std::chrono::high_resolution_clock::time_point lastFrame = std::chrono::high_resolution_clock::now();
    while (true)
    {
        for (auto session : server_broker->getClientsSessions())
        {
            receiveFromClient(server_broker, session, _ecs, chain);
        }
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - lastFrame;
        if (elapsed.count() >= 0.016)
        {
            lastFrame = now;
            _ecs->update(elapsed.count());
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

    attributeServerCallback(chain, *server_broker);

    std::shared_ptr<Ecs> _ecs = std::make_shared<Ecs>();
    Entity entity = _ecs->createEntity();
    _ecs->registerComponent<TransformComponent>();
    _ecs->registerComponent<MotionComponent>();

    Signature signature;
    _ecs->registerSystem<MoveSystem>();
    signature.set(_ecs->getComponentType<TransformComponent>());
    signature.set(_ecs->getComponentType<MotionComponent>());
    _ecs->setSignature<MoveSystem>(signature);

    int nbrPlayer = 0;
    chain.addActionCallback(asChar(ActionCode::READY), [&nbrPlayer, &server_broker](const Request &req, std::shared_ptr<Ecs>& _ecs) -> bool {
        nbrPlayer++;
        if (nbrPlayer != 2) {
            return false;
        }
        rtypeLog->log("Game is starting");
        Entity player1 = _ecs->createEntity();
        _ecs->addComponent<TransformComponent>(player1, {{0, 0, 0}, {0, 90, 0}, {1, 1, 1}});
        _ecs->addComponent<MotionComponent>(player1, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
        Entity player2 = _ecs->createEntity();
        _ecs->addComponent<TransformComponent>(player2, {{0, 0, 0}, {0, 90, 0}, {1, 1, 1}});
        _ecs->addComponent<MotionComponent>(player2, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
        Request request = {
            .header = {
                .MagicNumber = 0xFF,
                .EmmiterdEcsId = 0,
                .ReceiverEcsId = 0,
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
        server_broker->sendToAllClient(&msg, 1, 0);
        return true;
    });

    clock.addCallback([&server_broker, &_ecs, &nbrPlayer]() {
        if (nbrPlayer != 2) {
            return;
        }
        Request rq;
        rq.header.MagicNumber = 0xFF;
        rq.header.EmmiterdEcsId = 0;
        rq.header.ReceiverEcsId = 0;
        rq.header.TopicID = 1;
        rq.header.Action = asChar(ActionCode::UPDATE_ECS);
        rq.header.BodyLength = 0;
        UpdateEcs updateEcs1;
        updateEcs1.ecsId = 1;
        updateEcs1.position[0] = _ecs->getComponent<TransformComponent>(1).position.x;
        updateEcs1.position[1] = _ecs->getComponent<TransformComponent>(1).position.y;
        updateEcs1.position[2] = _ecs->getComponent<TransformComponent>(1).position.z;
        ::memmove(&rq.body._buffer, &updateEcs1, sizeof(UpdateEcs));
        UpdateEcs updateEcs2;
        updateEcs2.ecsId = 2;
        updateEcs2.position[0] = _ecs->getComponent<TransformComponent>(2).position.x;
        updateEcs2.position[1] = _ecs->getComponent<TransformComponent>(2).position.y;
        updateEcs2.position[2] = _ecs->getComponent<TransformComponent>(2).position.z;
        ::memmove((rq.body._buffer + sizeof(UpdateEcs)), &updateEcs2, sizeof(UpdateEcs));
        rq.header.BodyLength = sizeof(UpdateEcs) + sizeof(UpdateEcs);
        Message msg;
        msg.setRequest(rq);
        msg.setReliable(true);
        server_broker->sendToAllClient(&msg, 1, 0);
    }, 1000);

    clock.start();

    receivedFromAllClient(server_broker, _ecs, chain);

    delete server_broker;
    delete network_module;
    return 0;
}
