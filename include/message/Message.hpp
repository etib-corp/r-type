#pragma once

#include <cstdint>
#include <string>

class Message
{
public:
    ~Message(void) = default;

    void setECSId(std::uint32_t ecs_id) { _ecs_id = ecs_id; }

    std::uint32_t getECSId(void) const { return _ecs_id; }

    void setTopicName(const std::string topic_name) { _topic_name = topic_name; }

    const std::string &getTopicName(void) const { return _topic_name; }

private:
    std::uint32_t _ecs_id;
    std::string _topic_name;
};
