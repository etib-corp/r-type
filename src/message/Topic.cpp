#include "message/Topic.hpp"

Topic::Topic(std::uint32_t ecs_id, const std::string name, Type type)
    : _ecs_id(ecs_id), _name(name), _type(type)
{
}

Topic::~Topic(void)
{
}
