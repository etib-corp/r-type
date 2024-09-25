#include "message/Topic.hpp"

Topic::Topic(std::uint32_t ecs_id, const std::string name)
    : _ecs_id(ecs_id), _name(name)
{
}

Topic::~Topic(void)
{
}
