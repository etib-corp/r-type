/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CallBack
*/

#include "SenToAllClient.hpp"
#include "CallBack.hpp"

void callbackInputUp(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input UP executed." << std::endl;
    std::cout << "Before" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
    _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position[static_cast<int>(Axes3D::Y)] += 1;
    std::cout << "After" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
}

void callbackInputDown(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input Down executed." << std::endl;
    std::cout << "Before" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
    _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position[static_cast<int>(Axes3D::Y)] -= 1;
    std::cout << "After" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
}

void callbackInputLeft(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input Down executed." << std::endl;
    std::cout << "Before" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
    _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position[static_cast<int>(Axes3D::X)] -= 1;
    std::cout << "After" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
}

void callbackInputRight(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input Right executed." << std::endl;
    std::cout << "Before" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
    _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position[static_cast<int>(Axes3D::X)] += 1;
    std::cout << "After" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
}

void checkMagicNumber(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    if (header.MagicNumber == 0xFF)
    {
        std::cout << "Magic number checked." << std::endl;
        return;
    }
    std::cout << "Magic number not good." << std::endl;
}

void attributeServerCallback(ResponsibilityChain *chain, std::deque<std::shared_ptr<ISession>> sessions, ServerBroker *server_broker, Message *message)
{
    chain->addActionCallback(asChar(ActionCode::UP), checkMagicNumber);
    chain->addActionCallback(asChar(ActionCode::UP), callbackInputUp);
    chain->addActionCallback(asChar(ActionCode::UP), [sessions, server_broker, message](const Header &header, std::shared_ptr<Ecs> _ecs) { sendToAllClient(asChar(ActionCode::UP), sessions, server_broker, message); } );

    chain->addActionCallback(asChar(ActionCode::DOWN), checkMagicNumber);
    chain->addActionCallback(asChar(ActionCode::DOWN), callbackInputDown);
    chain->addActionCallback(asChar(ActionCode::DOWN), [sessions, server_broker, message](const Header &header, std::shared_ptr<Ecs> _ecs) { sendToAllClient(asChar(ActionCode::DOWN), sessions, server_broker, message); } );

    chain->addActionCallback(asChar(ActionCode::RIGHT), checkMagicNumber);
    chain->addActionCallback(asChar(ActionCode::RIGHT), callbackInputRight);
    chain->addActionCallback(asChar(ActionCode::RIGHT), [sessions, server_broker, message](const Header &header, std::shared_ptr<Ecs> _ecs) { sendToAllClient(asChar(ActionCode::RIGHT), sessions, server_broker, message); } );

    chain->addActionCallback(asChar(ActionCode::LEFT), checkMagicNumber);
    chain->addActionCallback(asChar(ActionCode::LEFT), callbackInputLeft);
    chain->addActionCallback(asChar(ActionCode::LEFT), [sessions, server_broker, message](const Header &header, std::shared_ptr<Ecs> _ecs) { sendToAllClient(asChar(ActionCode::LEFT), sessions, server_broker, message); } );
}

void executeCallbacks(
    const std::vector<std::function<void(
        const Header&, std::shared_ptr<Ecs>
    )>>& callbacks,
    const Header& header,
    std::shared_ptr<Ecs> _ecs
)
{
    for (const auto& callback : callbacks)
    {
        std::cout << header.Action << std::endl;
        callback(header, _ecs);
    }
}

void processHeader(const Header& header, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain)
{
    auto callbacks = chain.getActionCallbacks(header.Action);

    for (const auto& callback : callbacks)
    {
        callback(header, _ecs);
    }
}
