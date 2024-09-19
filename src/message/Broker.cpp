/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Broker.cpp
*/

#include "message/Broker.hpp"

void Broker::addTopic(const std::string &name)
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::unique_ptr<Topic> topic = std::make_unique<Topic>(name);
    _topics[name] = std::move(topic);
}

std::unique_ptr<Topic> &Broker::getTopic(const std::string &topicName)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_topics.find(topicName) == _topics.end())
        throw std::runtime_error("Topic not found");
    return _topics[topicName];
}

void Broker::removeTopic(const std::string &topicName)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _topics.erase(topicName);
}
