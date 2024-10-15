/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** CallbackClient
*/

#include "globalLogger.hpp"
#include "CallbackClient.hpp"
#include "LogDef.hpp"

bool callbackStartGame(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    rtypeLog->log("{}", "Game started.");
    StartGame sg;
    ::memmove(&sg, &req.body, sizeof(StartGame));
    rtypeLog->log("{} {}", "Number of player : ", static_cast<int>(sg.nbrPlayers));

    for (int i = 0; i < sg.nbrPlayers; i++) {
        Entity player = _ecs->createEntity();
        _ecs->addComponent<TransformComponent>(player, {{0, 0, 0}, {0, 90, 0}, {1, 1, 1}});
        ModelComponent *model = createModelComponent("assets/models/ship" + std::to_string(i) + "/ship" + std::to_string(i) + ".obj");
        _ecs->addComponent<ModelComponent>(player, *model);
        _ecs->addComponent<MotionComponent>(player, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    }
    return true;
}

bool callbackNewConnection(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "New connection." << std::endl;
    rtypeLog->log("{}", "New connection.");
    return true;
}

bool callbackUp(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    std::cout << "Up : " << static_cast<int>(id) << std::endl;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    if (motion.velocity[1] == 0.0f)
        motion.velocity[1] = 1.0f;
    else
        motion.velocity[1] = 0.0f;
    LE::Engine::getInstance()->debug("Up");
    rtypeLog->log<LogType::DEBUG>("{}", "Up");
    return true;
}

bool callbackDown(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    if (motion.velocity[1] == 0.0f)
        motion.velocity[1] = -1.0f;
    else
        motion.velocity[1] = 0.0f;
    rtypeLog->log<LogType::DEBUG>("{}", "Down");
    LE::Engine::getInstance()->debug("Down");
    return true;
}

bool callbackRight(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    if (motion.velocity[0] == 0.0f)
        motion.velocity[0] = 1.0f;
    else
        motion.velocity[0] = 0.0f;
    LE::Engine::getInstance()->debug("Right");
    rtypeLog->log<LogType::DEBUG>("{}", "Right");
    return true;
}

bool callbackLeft(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    if (motion.velocity[0] == 0.0f)
        motion.velocity[0] = -1.0f;
    else
        motion.velocity[0] = 0.0f;
    LE::Engine::getInstance()->debug("Left");
    rtypeLog->log<LogType::DEBUG>("{}", "Left");
    return true;
}

bool callbackShoot(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto transform = _ecs->getComponent<TransformComponent>(id);
    Entity entity = _ecs->createEntity();
    _ecs->addComponent<TransformComponent>(entity, (TransformComponent){transform.position, {0, 0, 0}, {1.0f, 1.0f, 1.0f}});
    _ecs->addComponent<MotionComponent>(entity, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    _ecs->addComponent<PatternComponent>(entity, (PatternComponent){"line", LE::Vector3<float>(transform.position.x + 50, transform.position.y, transform.position.z), 0.1, PatternEnd::DESTROY});
    ModelComponent *model = createModelComponent("assets/models/bullet/bullet.obj");
    _ecs->addComponent<ModelComponent>(entity, *model);
    std::cout << "SHIP " << id << " SHOOT" << std::endl;
    return true;
}

bool checkMagicNumber(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    if (req.header.MagicNumber == 0xFF)
    {
        rtypeLog->log<LogType::DEBUG>("{}", "Magic number checked.");
        return true;
    }
    rtypeLog->log<LogType::DEBUG>("{}", "Magic number not good.");
    return false;
}

void attributeClientCallback(ResponsibilityChain *chain, ClientBroker *client_broker)
{
    chain->addActionCallback(asChar(ActionCode::START_GAME), callbackStartGame);

    chain->addActionCallback(asChar(ActionCode::NEW_CONNECTION), callbackNewConnection);

    chain->addActionCallback(asChar(ActionCode::UP), callbackUp);

    chain->addActionCallback(asChar(ActionCode::DOWN), callbackDown);

    chain->addActionCallback(asChar(ActionCode::RIGHT), callbackRight);

    chain->addActionCallback(asChar(ActionCode::LEFT), callbackLeft);

    chain->addActionCallback(asChar(ActionCode::SHOOT), callbackShoot);
}
