/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** CallbackClient
*/

#include "CallbackClient.hpp"

void callbackStartGame(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Game started." << std::endl;
    StartGame sg;
    ::memmove(&sg, &req.body, sizeof(StartGame));
    std::cout << "Number of player : " << (int)sg.nbrPlayers << std::endl;
    for (int i = 0; i < sg.nbrPlayers; i++) {
        Entity player = _ecs->createEntity();
        _ecs->addComponent<TransformComponent>(player, {{0, 0, 0}, {0, 90, 0}, {1, 1, 1}});
        ModelComponent *model = createModelComponent("assets/models/ship" + std::to_string(i) + "/ship" + std::to_string(i) + ".obj");
        _ecs->addComponent<ModelComponent>(player, *model);
        _ecs->addComponent<MotionComponent>(player, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    }
}

void callbackNewConnection(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "New connection." << std::endl;
}

void callbackUp(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.ReceiverEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    if (motion.velocity[1] == 0.0f)
        motion.velocity[1] = 1.0f;
    else
        motion.velocity[1] = 0.0f;
    LE::Engine::getInstance()->debug("Up");
}

void callbackDown(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.ReceiverEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    if (motion.velocity[1] == 0.0f)
        motion.velocity[1] = -1.0f;
    else
        motion.velocity[1] = 0.0f;
    LE::Engine::getInstance()->debug("Down");
}

void callbackRight(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.ReceiverEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    if (motion.velocity[0] == 0.0f)
        motion.velocity[0] = 1.0f;
    else
        motion.velocity[0] = 0.0f;
    LE::Engine::getInstance()->debug("Right");
}

void callbackLeft(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.ReceiverEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    if (motion.velocity[0] == 0.0f)
        motion.velocity[0] = -1.0f;
    else
        motion.velocity[0] = 0.0f;
    LE::Engine::getInstance()->debug("Left");
}

void checkMagicNumber(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    if (req.header.MagicNumber == 0xFF)
    {
        std::cout << "Magic number checked." << std::endl;
        return;
    }
    std::cout << "Magic number not good." << std::endl;
}

void attributeClientCallback(ResponsibilityChain *chain, ClientBroker *client_broker)
{
    chain->addActionCallback(asChar(ActionCode::START_GAME), callbackStartGame);

    chain->addActionCallback(asChar(ActionCode::NEW_CONNECTION), callbackNewConnection);

    chain->addActionCallback(asChar(ActionCode::UP), callbackUp);

    chain->addActionCallback(asChar(ActionCode::DOWN), callbackDown);

    chain->addActionCallback(asChar(ActionCode::RIGHT), callbackRight);

    chain->addActionCallback(asChar(ActionCode::LEFT), callbackLeft);
}
