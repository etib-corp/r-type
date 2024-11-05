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

int _main()
{
    // LE::GraphicalLib lib("/home/hugo/tek3/r-type-ref/build/dependencies/lion-engine/lib/SFML/liblion-engine-SFML.so");
    LE::GraphicalLib lib("/home/sleo/etib/r-type/build/dependencies/lion-engine/lib/SFML/liblion-engine-SFML.so");
    g_engine = lib.createEngine();

    // g_engine->init();

    g_engine->setFramerateLimit(60);

    // g_engine->setGame<ServerGame>();

    // auto scene = g_engine->addScene<LE::Scene>("Default");

    // scene->getEcs()->createEntity();

    // g_engine->playScene("Default");

    // g_engine->run(true);
    return 0;
}

#include "luacpp/luacpp.h"
#include <iostream>
#include <string>
#include <vector>

class Enemy {
public:
    std::string texture_obj;
    std::vector<int> start_pos;
    std::vector<int> end_pos;
    float speed;
    int life;
    int damage;
    std::string pattern;
    int scale;
    std::vector<int> rotation;

    struct Box {
        int height;
        int width;
        std::vector<int> layers;
        std::vector<int> masks;
    };

    Box hurtbox;
    Box hitbox;

    void Print() const {
        std::cout << "Enemy:\n";
        std::cout << "  texture_obj: " << texture_obj << "\n";
        std::cout << "  start_pos: [" << start_pos[0] << ", " << start_pos[1] << ", " << start_pos[2] << "]\n";
        std::cout << "  end_pos: [" << end_pos[0] << ", " << end_pos[1] << ", " << end_pos[2] << "]\n";
        std::cout << "  speed: " << speed << "\n";
        std::cout << "  life: " << life << "\n";
        std::cout << "  damage: " << damage << "\n";
        std::cout << "  pattern: " << pattern << "\n";
        std::cout << "  scale: " << scale << "\n";
        std::cout << "  rotation: [" << rotation[0] << ", " << rotation[1] << ", " << rotation[2] << "]\n";
        std::cout << "  hurtbox: { height: " << hurtbox.height << ", width: " << hurtbox.width << ", layers:" << hurtbox.layers[0] << " , mask:" << hurtbox.masks[0] << " }\n";
        std::cout << "  hitbox: { height: " << hitbox.height << ", width: " << hitbox.width << " }\n";
    }
};

std::vector<int> ConvertLuaTableToVector(const luacpp::LuaTable& luaTable) {
    std::vector<int> result;

    luaTable.ForEach([&result](const luacpp::LuaObject& key, const luacpp::LuaObject& value) -> bool {
        if (value.GetType() == LUA_TNUMBER) {
            result.push_back(value.ToInteger());
            std::cout << "ToInteger= " << value.ToInteger() << std::endl;
        }
        return true;
    });

    return result;
}

Enemy CreateEnemyFromLua(const luacpp::LuaTable& enemyTable) {
    Enemy enemy;

    // Charger les attributs de base
    enemy.texture_obj = enemyTable.Get("texture_obj").ToString();

    luacpp::LuaTable startPosTable = enemyTable.Get("start_pos");
    startPosTable.ForEach([&enemy](const luacpp::LuaObject& key, const luacpp::LuaObject& value) -> bool {
        enemy.start_pos.push_back(value.ToInteger());
        return true;
    });

    luacpp::LuaTable endPosTable = enemyTable.Get("end_pos");
    endPosTable.ForEach([&enemy](const luacpp::LuaObject& key, const luacpp::LuaObject& value) -> bool {
        enemy.end_pos.push_back(value.ToInteger());
        return true;
    });

    luacpp::LuaTable rotationTable = enemyTable.Get("rotation");
    rotationTable.ForEach([&enemy](const luacpp::LuaObject& key, const luacpp::LuaObject& value) -> bool {
        enemy.rotation.push_back(value.ToInteger());
        return true;
    });

    enemy.speed = enemyTable.Get("speed").ToNumber();
    enemy.life = enemyTable.Get("life").ToInteger();
    enemy.damage = enemyTable.Get("damage").ToInteger();
    enemy.pattern = enemyTable.Get("pattern").ToString();
    enemy.scale = enemyTable.Get("scale").ToInteger();

    // Charger les sous-tables (hurtbox et hitbox)
    luacpp::LuaTable hurtboxTable = enemyTable.Get("hurtbox");
    enemy.hurtbox.height = hurtboxTable.Get("height").ToInteger();
    enemy.hurtbox.width = hurtboxTable.Get("width").ToInteger();
    luacpp::LuaTable hurtboxLayersTables = hurtboxTable.Get("layers");
    enemy.hurtbox.layers = ConvertLuaTableToVector(hurtboxLayersTables);
    // enemy.hurtbox.masks =  ConvertLuaTableToVector(hurtboxTable.Get("masks").ToPointer());

    // Convertir les objets en LuaTable avant l'itération
    luacpp::LuaTable hurtboxLayersTable = hurtboxTable.Get("layers");
    hurtboxLayersTable.ForEach([&enemy](const luacpp::LuaObject& key, const luacpp::LuaObject& value) -> bool {
        enemy.hurtbox.layers.push_back(value.ToInteger());
        return true;
    });

    luacpp::LuaTable hurtboxMasksTable = hurtboxTable.Get("masks");
    hurtboxMasksTable.ForEach([&enemy](const luacpp::LuaObject& key, const luacpp::LuaObject& value) -> bool {
        enemy.hurtbox.masks.push_back(value.ToInteger());
        return true;
    });

    luacpp::LuaTable hitboxTable = enemyTable.Get("hitbox");
    enemy.hitbox.height = hitboxTable.Get("height").ToInteger();
    enemy.hitbox.width = hitboxTable.Get("width").ToInteger();

    luacpp::LuaTable hitboxLayersTable = hitboxTable.Get("layers");
    hitboxLayersTable.ForEach([&enemy](const luacpp::LuaObject& key, const luacpp::LuaObject& value) -> bool {
        enemy.hitbox.layers.push_back(value.ToInteger());
        return true;
    });

    luacpp::LuaTable hitboxMasksTable = hitboxTable.Get("masks");
    hitboxMasksTable.ForEach([&enemy](const luacpp::LuaObject& key, const luacpp::LuaObject& value) -> bool {
        enemy.hitbox.masks.push_back(value.ToInteger());
        return true;
    });

    return enemy;
}

#include <vector>

int main(int ac, char **av)
{
    g_engine = instanciateEngine();

    g_engine->setGame<ServerGame>();

    auto scene = g_engine->addScene<LE::Scene>("Default");

    scene->getEcs()->createEntity();

    g_engine->playScene("Default");

    g_engine->run(true);

    return 0;
}
