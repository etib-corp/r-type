#include "message/Topic.hpp"

Topic::Topic(std::uint8_t ecs_id, std::uint8_t id)
    : _ecs_id(ecs_id), _id(id)
{
}

Topic::~Topic(void)
{
}

void Topic::addMessage(Message *message)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _messages.push(message);
}

Message *Topic::getMessage(void)
{
    Message *message = nullptr;
    std::lock_guard<std::mutex> lock(_mutex);
    if (_messages.empty()) {
        return nullptr;
    }
    message = _messages.front();
    _messages.pop();
    return message;
}
