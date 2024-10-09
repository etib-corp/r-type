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
    std::cout << "Number of player : " << sg.nbrPlayers << std::endl;
    for (int i = 0; i < sg.nbrPlayers; i++) {
        Entity player = _ecs->createEntity();
        _ecs->addComponent<TransformComponent>(player, {{50.0f * (static_cast<float>(i) + 1.0f), 0, 0}, {0, 90, 0}, {1, 1, 1}});
        ModelComponent *model = createModelComponent("assets/models/ship/ship" + std::to_string(i) + ".obj");
        _ecs->addComponent<ModelComponent>(player, *model);
        _ecs->addComponent<MotionComponent>(player, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    }
}

void callbackNewConnection(const Request& req, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "New connection." << std::endl;
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
}
