/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CallbackClient
*/

#include "CallbackClient.hpp"

bool callbackStartGame(const Request& req, const std::shared_ptr<LE::Ecs> &_ecs)
{
    // rtypeLog->log("{}", "Game started.");
    StartGame sg;
    ::memmove(&sg, &req.body, sizeof(StartGame));
    // rtypeLog->log("{} {}", "Number of player : ", static_cast<int>(sg.nbrPlayers));

    for (int i = 0; i < sg.nbrPlayers; i++) {
        Entity player = _ecs->createEntity();
        _ecs->addComponent<TransformComponent>(player, {{0, 0, 0}, {0, 90, 0}, {1, 1, 1}});
        std::shared_ptr<LE::ISpriteComponent> sprite = g_engine->createSpriteComponent("assets/images/player.png");
        _ecs->addComponent<std::shared_ptr<LE::ISpriteComponent>>(player, sprite);
        _ecs->addComponent<MotionComponent>(player, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    }
    g_engine->restartClock();
    return true;
}

bool callbackUp(const Request& req, std::shared_ptr<LE::Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    std::cout << "Up : " << static_cast<int>(id) << std::endl;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    motion.direction[MOVEMENT_UP] = motion.direction[MOVEMENT_UP] == 0 ? 1 : 0;
    // rtypeLog->log<LogType::DEBUG>("{}", "Up");
    return true;
}

void attributeClientCallback(std::shared_ptr<LE::ResponsibilityChain> chain, std::shared_ptr<LE::ClientBroker> client_broker)
{
    chain->addActionCallback(asChar(ActionCode::START_GAME), callbackStartGame);

    chain->addActionCallback(asChar(ActionCode::UP), callbackUp);
}