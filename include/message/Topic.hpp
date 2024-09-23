#pragma once

#include <cstdint>
#include <string>
#include <queue>
#include <memory>

#include "message/Message.hpp"

class Topic
{
public:
    Topic(std::uint32_t ecs_id, const std::string name)
        : _ecs_id(ecs_id), _name(name) {}

    ~Topic(void) {}

    void addMessage(std::unique_ptr<Message> message)
    {
        _messages.push(std::move(message));
    }

    std::unique_ptr<Message> getMessage(void)
    {
        if (_messages.empty())
            return nullptr;
        auto message = std::move(_messages.front());
        _messages.pop();
        return message;
    }

private:
    std::uint32_t _ecs_id;
    std::string _name;
    std::queue<std::unique_ptr<Message>> _messages;
};
