/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "interface/IEngine.hpp"
#include "GraphicalLib.hpp"
#include "Common.hpp"
#include <iostream>
#include <chrono>
#include "CallbackServer.hpp"

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

static void receiveFromClient(std::shared_ptr<LE::ServerBroker> server_broker, std::shared_ptr<ISession> session, std::shared_ptr<LE::Ecs> _ecs, std::shared_ptr<LE::ResponsibilityChain> chain)
{
    try {
        std::shared_ptr<LE::Message> message = nullptr;
        message = server_broker->getMessage(session->getId(), 1);
        if (message == nullptr) {
            return;
        }
        Request req = message->getRequest();
        processRequest(req, _ecs, chain);
    } catch (const std::exception &e) {
    }
}

static void receivedFromAllClient(std::shared_ptr<LE::ServerBroker> server_broker, std::shared_ptr<LE::Ecs> _ecs, std::shared_ptr<LE::ResponsibilityChain> chain)
{
    for (auto session : server_broker->getClientsSessions())
    {
        receiveFromClient(server_broker, session, _ecs, chain);
    }
}

std::shared_ptr<LE::IEngine> g_engine;

class ServerGame : public LE::IGame
{
    public :
        void init(LE::IEngine &engine) override
        {
            _sceneManager = g_engine->createSceneManager();
            _serverBroker = std::make_shared<LE::ServerBroker>(g_engine->getNetworkModule(), 0, 8080);
            _responsibilityChain = std::make_shared<LE::ResponsibilityChain>();

            attributeServerCallback(_serverBroker, _responsibilityChain);

            _nbrPlayer = 0;

            _responsibilityChain->addActionCallback(asChar(ActionCode::READY), [this](const Request &req, std::shared_ptr<LE::Ecs>& _ecs) -> bool {
                _nbrPlayer++;
                std::cout << "nbrPlayer=" << _nbrPlayer << std::endl;
                if (_nbrPlayer != 2) {
                    return false;
                }
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
                startGame.nbrPlayers = _nbrPlayer;
                ::memmove(request.body._buffer, &startGame, sizeof(StartGame));
                std::shared_ptr<LE::Message> msg = std::make_shared<LE::Message>();
                msg->setRequest(request);
                msg->setReliable(true);
                _serverBroker->sendToAllClient(msg, 1, 0);
                clock.start();
                return true;
            });

            clock.addCallback([this]() {
                if (_nbrPlayer != 2) {
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
                std::shared_ptr<LE::Ecs> _ecs = _sceneManager->getCurrentScene()->getEcs();
                updateEcs1.position[0] = _ecs->getComponent<TransformComponent>(1).position.x;
                updateEcs1.position[1] = _ecs->getComponent<TransformComponent>(1).position.y;
                updateEcs1.position[2] = _ecs->getComponent<TransformComponent>(1).position.z;
                ::memmove(&rq.body._buffer, &updateEcs1, sizeof(UpdateEcs));
                UpdateEcs updateEcs2;
                updateEcs2.ecsId = 2;
                updateEcs2.position[0] = _ecs->getComponent<TransformComponent>(2).position.x;
                updateEcs2.position[1] = _ecs->getComponent<TransformComponent>(2).position.y;
                updateEcs2.position[2] = _ecs->getComponent<TransformComponent>(2).position.z;
                ::memmove(&rq.body._buffer[sizeof(UpdateEcs)], &updateEcs2, sizeof(UpdateEcs));
                rq.header.BodyLength = sizeof(UpdateEcs) + sizeof(UpdateEcs);
                std::shared_ptr<LE::Message> msg = std::make_shared<LE::Message>();
                msg->setRequest(rq);
                msg->setReliable(true);
                _serverBroker->sendToAllClient(msg, 1, 0);
            }, 1000);

            // clock.addCallback([this]() {
            //     std::shared_ptr<LE::Ecs> _ecs = _sceneManager->getCurrentScene()->getEcs();
            //     _ecs->update(0.016);
            // }, 16);

        }

        void update() override
        {
            receivedFromAllClient(_serverBroker, _sceneManager->getCurrentScene()->getEcs(), _responsibilityChain);
        }

        LE::Clock clock;
        int _nbrPlayer;
};

int main()
{
    LE::GraphicalLib lib("/home/sleo/etib/r-type/build/dependencies/lion-engine/lib/SFML/liblion-engine-SFML.so");
    g_engine = lib.createEngine();

    g_engine->init();

    g_engine->setFramerateLimit(60);

    g_engine->setGame<ServerGame>();

    auto scene = g_engine->addScene<LE::Scene>("Default");

    scene->getEcs()->createEntity();

    g_engine->playScene("Default");

    g_engine->run(true);
    return 0;
}
