/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** CallbackServer
*/

#include "CallbackServer.hpp"

bool callbackInputUp(const Request &req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    rtypeLog->log("{}", "Up");
    auto &motion = _ecs->getComponent<MotionComponent>(id);
    motion.direction[MOVEMENT_UP] = motion.direction[MOVEMENT_UP] == 0 ? 1 : 0;
    return true;
}

bool callbackInputDown(const Request &req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto &motion = _ecs->getComponent<MotionComponent>(id);
    motion.direction[MOVEMENT_DOWN] = motion.direction[MOVEMENT_DOWN] == 0 ? 1 : 0;
    return true;
}

bool callbackInputRight(const Request &req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto &motion = _ecs->getComponent<MotionComponent>(id);
    motion.direction[MOVEMENT_RIGHT] = motion.direction[MOVEMENT_RIGHT] == 0 ? 1 : 0;
    return true;
}

bool callbackInputLeft(const Request &req, std::shared_ptr<Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto &motion = _ecs->getComponent<MotionComponent>(id);
    motion.direction[MOVEMENT_LEFT] = motion.direction[MOVEMENT_LEFT] == 0 ? 1 : 0;
    return true;
}

bool checkMagicNumber(const Request &req, std::shared_ptr<Ecs> _ecs)
{
    if (req.header.MagicNumber == 0xFF)
    {
        rtypeLog->log("{}", "Magic number good.");
        return true;
    }
    rtypeLog->log("{}", "Magic number not good.");
    return false;
}

void attributeServerCallback(ResponsibilityChain &chain, ServerBroker &server_broker)
{
    std::shared_ptr<Message> message = std::make_shared<Message>();
    Request request = {
        .header = {
            .MagicNumber = 0xFF,
            .EmmiterdEcsId = 0x00,
            .ReceiverEcsId = 0x00,
            .TopicID = 0x00,
            .Action = 0x00,
            .BodyLength = 0},
        .body = {0}};
    message->setRequest(request);


    // chain->addActionCallback(asChar(ActionCode::UP), checkMagicNumber);
    chain.addActionCallback(asChar(ActionCode::UP), callbackInputUp);
    chain.addActionCallback(asChar(ActionCode::UP), [&server_broker, message](const Request &req, std::shared_ptr<Ecs> _ecs) -> bool
                             {
        message->setAction(asChar(ActionCode::UP));
        server_broker.sendToAllClient(message.get(), 1, req.header.EmmiterdEcsId);
        return true;
    });

    // chain.addActionCallback(asChar(ActionCode::DOWN), checkMagicNumber);
    chain.addActionCallback(asChar(ActionCode::DOWN), callbackInputDown);
    chain.addActionCallback(asChar(ActionCode::DOWN), [&server_broker, message](const Request &req, std::shared_ptr<Ecs> _ecs) -> bool
                             {
                message->setAction(asChar(ActionCode::DOWN));
        server_broker.sendToAllClient(message.get(), 1, req.header.EmmiterdEcsId);
        return true;
    });

    // chain.addActionCallback(asChar(ActionCode::RIGHT), checkMagicNumber);
    chain.addActionCallback(asChar(ActionCode::RIGHT), callbackInputRight);
    chain.addActionCallback(asChar(ActionCode::RIGHT), [&server_broker, message](const Request &req, std::shared_ptr<Ecs> _ecs) -> bool
                             {
               message->setAction(asChar(ActionCode::RIGHT));
        server_broker.sendToAllClient(message.get(), 1, req.header.EmmiterdEcsId);
        return true;
    });

    // chain.addActionCallback(asChar(ActionCode::LEFT), checkMagicNumber);
    chain.addActionCallback(asChar(ActionCode::LEFT), callbackInputLeft);
    chain.addActionCallback(asChar(ActionCode::LEFT), [&server_broker, message](const Request &req, std::shared_ptr<Ecs> _ecs) -> bool
                             {
                message->setAction(asChar(ActionCode::LEFT));
        server_broker.sendToAllClient(message.get(), 1, req.header.EmmiterdEcsId);
    return true;
    });


    chain.addActionCallback(asChar(ActionCode::SHOOT), [&server_broker, message](const Request &req, std::shared_ptr<Ecs> _ecs) -> bool
                             {
        message->setAction(asChar(ActionCode::SHOOT));
        server_broker.sendToAllClient(message.get(), 1, req.header.EmmiterdEcsId);
        return true;
    });
}
