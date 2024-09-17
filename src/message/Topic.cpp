/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Topic.cpp
*/

#include "message/Topic.hpp"

Topic::Topic(std::string name) : _name(name)
{
}

Topic::~Topic(void)
{
}

void Topic::produceMessage(std::unique_ptr<Message> message)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _messages.push(std::move(message));
}

std::unique_ptr<Message> Topic::consumeMessage(void)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_messages.empty())
        return nullptr;
    std::unique_ptr<Message> message = std::move(_messages.front());
    _messages.pop();
    return message;
}
