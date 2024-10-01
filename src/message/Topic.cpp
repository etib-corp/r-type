#include "message/Topic.hpp"

Topic::Topic(std::uint32_t ecs_id, std::uint8_t id)
    : _ecs_id(ecs_id), _id(id)
{
}

Topic::~Topic(void)
{
}
