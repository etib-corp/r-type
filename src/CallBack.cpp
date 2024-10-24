/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CallBack
*/

#include "CallBack.hpp"

// void callbackInputUp(const Request& req, std::shared_ptr<Ecs> _ecs)
// {
//     std::cout << "Callback Input UP executed." << std::endl;
//     std::cout << "Before" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
//     _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position[static_cast<int>(Axes3D::Y)] += 1;
//     std::cout << "After" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
// }

// void callbackInputDown(const Request& req, std::shared_ptr<Ecs> _ecs)
// {
//     std::cout << "Callback Input Down executed." << std::endl;
//     std::cout << "Before" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
//     _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position[static_cast<int>(Axes3D::Y)] -= 1;
//     std::cout << "After" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
// }

// void callbackInputLeft(const Request& req, std::shared_ptr<Ecs> _ecs)
// {
//     std::cout << "Callback Input Down executed." << std::endl;
//     std::cout << "Before" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
//     _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position[static_cast<int>(Axes3D::X)] -= 1;
//     std::cout << "After" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
// }

// void callbackInputRight(const Request& req, std::shared_ptr<Ecs> _ecs)
// {
//     std::cout << "Callback Input Right executed." << std::endl;
//     std::cout << "Before" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
//     _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position[static_cast<int>(Axes3D::X)] += 1;
//     std::cout << "After" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
// }

// void checkMagicNumber(const Request& req, std::shared_ptr<Ecs> _ecs)
// {
//     if (req.header.MagicNumber == 0xFF)
//     {
//         std::cout << "Magic number checked." << std::endl;
//         return;
//     }
//     std::cout << "Magic number not good." << std::endl;
// }

// void attributeServerCallback(ResponsibilityChain *chain, std::deque<std::shared_ptr<ISession>> sessions, ServerBroker *server_broker)
// {
//     chain->addActionCallback(asChar(ActionCode::UP), checkMagicNumber);
//     chain->addActionCallback(asChar(ActionCode::UP), callbackInputUp);
//     chain->addActionCallback(asChar(ActionCode::UP), [sessions, server_broker](const Request &req, std::shared_ptr<Ecs> _ecs) { sendToAllClient(asChar(ActionCode::UP), sessions, server_broker); } );

//     chain->addActionCallback(asChar(ActionCode::DOWN), checkMagicNumber);
//     chain->addActionCallback(asChar(ActionCode::DOWN), callbackInputDown);
//     chain->addActionCallback(asChar(ActionCode::DOWN), [sessions, server_broker](const Request &req, std::shared_ptr<Ecs> _ecs) { sendToAllClient(asChar(ActionCode::DOWN), sessions, server_broker); } );

//     chain->addActionCallback(asChar(ActionCode::RIGHT), checkMagicNumber);
//     chain->addActionCallback(asChar(ActionCode::RIGHT), callbackInputRight);
//     chain->addActionCallback(asChar(ActionCode::RIGHT), [sessions, server_broker](const Request &req, std::shared_ptr<Ecs> _ecs) { sendToAllClient(asChar(ActionCode::RIGHT), sessions, server_broker); } );

//     chain->addActionCallback(asChar(ActionCode::LEFT), checkMagicNumber);
//     chain->addActionCallback(asChar(ActionCode::LEFT), callbackInputLeft);
//     chain->addActionCallback(asChar(ActionCode::LEFT), [sessions, server_broker](const Request &req, std::shared_ptr<Ecs> _ecs) { sendToAllClient(asChar(ActionCode::LEFT), sessions, server_broker); } );
// }

void executeCallbacks(
    const std::vector<std::function<void(
        const Request&, std::shared_ptr<Ecs>
    )>>& callbacks,
    const Request& req,
    std::shared_ptr<Ecs> _ecs
)
{
    for (const auto& callback : callbacks)
    {
        std::cout << req.header.Action << std::endl;
        callback(req, _ecs);
    }
}

void processRequest(const Request& req, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain)
{
    auto callbacks = chain.getActionCallbacks(req.header.Action);
    bool callbackState = false;

    for (const auto& callback : callbacks)
    {
        callbackState =  callback(req, _ecs);
        if (!callbackState)
        {
            rtypeLog->log<LogType::WARN>("THE CHAIN HAS BEEN BROKEN");
            break;
        }
        rtypeLog->log<LogType::DEBUG>("callback state = {}", callbackState);
    }
}
