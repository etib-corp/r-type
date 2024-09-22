#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <memory>

#include "message/Topic.hpp"

class Broker
{
public:
    ~Broker(void) = default;

    void setECSId(std::uint32_t ecs_id) { _ecs_id = ecs_id; }

    std::uint32_t getECSId(void) const { return _ecs_id; }

    void addTopic(std::uint32_t ecs_id, const std::string &name)
    {
        _topics[std::make_pair(ecs_id, name)] = std::make_unique<Topic>(ecs_id, name);
    }

    std::unique_ptr<Topic> &getTopic(std::uint32_t ecs_id, const std::string &name)
    {
        if (_topics.find(std::make_pair(ecs_id, name)) == _topics.end())
            throw std::runtime_error("Topic not found");
        return _topics[std::make_pair(ecs_id, name)];
    }

    void removeTopic(std::uint32_t ecs_id, const std::string &name)
    {
        _topics.erase(std::make_pair(ecs_id, name));
    }

    virtual void addMessage(std::uint32_t ecs_id, const std::string &topic_name, std::unique_ptr<Message> message) = 0;

    std::unique_ptr<Message> getMessage(std::uint32_t ecs_id, const std::string &topic_name)
    {
        return getTopic(ecs_id, topic_name)->getMessage();
    }

private:
    std::uint32_t _ecs_id;
    std::map<std::pair<std::uint32_t, std::string>, std::unique_ptr<Topic>> _topics;
};
