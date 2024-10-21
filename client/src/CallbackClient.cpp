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
        ModelComponent *model = createModelComponent("assets/models/ship" + std::to_string(1) + "/ship" + std::to_string(1) + ".obj");
        _ecs->addComponent<ModelComponent>(player, *model);
        _ecs->addComponent<MotionComponent>(player, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    }
    LE::Engine::getInstance()->restartClock();
    return true;
}


bool callbackUp(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    std::cout << "Up : " << static_cast<int>(id) << std::endl;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    motion.velocity[1] = 1.0f;
    LE::Engine::getInstance()->debug("Up");
    rtypeLog->log<LogType::DEBUG>("{}", "Up");
    return true;
}

bool callbackStopUp(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    motion.velocity[1] = 0.0f;
    rtypeLog->log<LogType::DEBUG>("{}", "Stop Up");
    LE::Engine::getInstance()->debug("Stop Up");
    return true;
}

bool callbackDown(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    motion.velocity[1] = -1.0f;
    rtypeLog->log<LogType::DEBUG>("{}", "Down");
    LE::Engine::getInstance()->debug("Down");
    return true;
}

bool callbackStopDown(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    motion.velocity[1] = 0.0f;
    rtypeLog->log<LogType::DEBUG>("{}", "Stop Down");
    LE::Engine::getInstance()->debug("Stop Down");
    return true;
}

bool callbackRight(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    auto& transform = _ecs->getComponent<TransformComponent>(id);
    LE::Vector3Data<float> vectorData;
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
    auto transform = _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId);
    Entity entity = _ecs->createEntity();
    _ecs->addComponent<TransformComponent>(entity, (TransformComponent){{transform.position.x + 3, transform.position.y + 0.3f, transform.position.z}, {0, 0, 0}, {0.3f, 0.1f, 0.1f}});
    _ecs->addComponent<MotionComponent>(entity, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    _ecs->addComponent<PatternComponent>(entity, (PatternComponent){"line", LE::Vector3<float>(transform.position.x + 50, transform.position.y + 0.3f, transform.position.z), 0.1, PatternEnd::DESTROY});
    HitBox hitbox = {5, 5, 0, 0};
    hitbox.masks.set(3);
    _ecs->addComponent<HitBox>(entity, hitbox);
    _ecs->addComponent<HurtBox>(entity, (HurtBox){5, 5, 0, 0, []() {
        std::cout << "Hurtbox on hit" << std::endl;
    }});
    ModelComponent *model = createModelComponent("assets/models/bullet/bullet.obj");

    _ecs->addComponent<ModelComponent>(entity, *model);
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

bool callbackUpdateEcs(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    UpdateEcs updateEcs1;
    UpdateEcs updateEcs2;
    ::memmove(&updateEcs1, &req.body._buffer, sizeof(UpdateEcs));
    ::memmove(&updateEcs2, &req.body._buffer[sizeof(updateEcs1)], sizeof(UpdateEcs));
    std::cout << "UpdateEcs1 : " << static_cast<int>(updateEcs1.ecsId) << std::endl;
    std::cout << "UpdateEcs2 : " << static_cast<int>(updateEcs2.ecsId) << std::endl;
    std::cout << updateEcs1.position[0] << "  " <<  updateEcs1.position[1] << "  " << updateEcs1.position[2] << std::endl;
    _ecs->getComponent<TransformComponent>(updateEcs1.ecsId).position = {updateEcs1.position[0], updateEcs1.position[1], updateEcs1.position[2]};
    _ecs->getComponent<TransformComponent>(updateEcs2.ecsId).position = {updateEcs2.position[0], updateEcs2.position[1], updateEcs2.position[2]};
    return true;
}

void attributeClientCallback(ResponsibilityChain *chain, ClientBroker *client_broker)
{

    std::function<bool(const Request &, std::shared_ptr<Ecs>)> checkRequestEmmiterdEcsId = [client_broker](const Request &req, std::shared_ptr<Ecs> _ecs) {
        if (req.header.EmmiterdEcsId == client_broker->getECSId()) {
            rtypeLog->log<LogType::DEBUG>("{}", "Request emmiterd ecs id checked.");
            return false;
        }
        return true;
    };


    chain->addActionCallback(asChar(ActionCode::START_GAME), callbackStartGame);


    // chain->addActionCallback(asChar(ActionCode::UP), checkRequestEmmiterdEcsId);
    chain->addActionCallback(asChar(ActionCode::UP), callbackUp);

    chain->addActionCallback(asChar(ActionCode::STOP_UP), callbackStopUp);

    // chain->addActionCallback(asChar(ActionCode::DOWN), checkRequestEmmiterdEcsId);
    chain->addActionCallback(asChar(ActionCode::DOWN), callbackDown);

    chain->addActionCallback(asChar(ActionCode::STOP_DOWN), callbackStopDown);

    // chain->addActionCallback(asChar(ActionCode::RIGHT), checkRequestEmmiterdEcsId);
    chain->addActionCallback(asChar(ActionCode::RIGHT), callbackRight);

    // chain->addActionCallback(asChar(ActionCode::LEFT), checkRequestEmmiterdEcsId);
    chain->addActionCallback(asChar(ActionCode::LEFT), callbackLeft);

    // chain->addActionCallback(asChar(ActionCode::SHOOT), checkRequestEmmiterdEcsId);
    chain->addActionCallback(asChar(ActionCode::SHOOT), callbackShoot);

    chain->addActionCallback(asChar(ActionCode::UPDATE_ECS), callbackUpdateEcs);
}
