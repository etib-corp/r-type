#include "message/Message.hpp"

Message::Message(void) : _ecs_id(0), _topic_name(0), _action(0)
{
}

Message::~Message(void)
{
}

std::unique_ptr<Request> Message::serialize(void) const
{
    std::unique_ptr<Request> request = std::make_unique<Request>();

    request->header.MagicNumber = 0x77;
    request->header.ECS_CLIENT_ID = _ecs_id;
    request->header.Action = _action;
    request->header.BodyLength = 0;
    std::memset(request->body._buffer, 0, 1024);
    return std::move(request);
}

void Message::deserialize(std::unique_ptr<Request> request)
{
    if (request->header.MagicNumber != 0x77)
        throw std::runtime_error("Invalid magic number");
    _ecs_id = request->header.ECS_CLIENT_ID;
    _action = request->header.Action;
}