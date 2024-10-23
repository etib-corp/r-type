/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** PatternSystem
*/

#include "ECS/Systems/PatternSystem.hpp"
#include <ECS/Ecs.hpp>

PatternSystem::PatternSystem()
{
}

PatternSystem::~PatternSystem()
{
}

void PatternSystem::update(Ecs *ecs, float dt)
{
    for (auto &entity : _entities) {
        auto &pattern = ecs->getComponent<PatternComponent>(entity);
        auto &transform = ecs->getComponent<TransformComponent>(entity);

        pattern.velocity = {0, 0, 0};

        if (pattern.end_pos == transform.position && pattern.end == DESTROY) {
            std::cout << "Destroying entity" << std::endl;
            ecs->destroyEntity(entity);
        }

        _patterns[pattern.pattern_name](pattern, transform);
        if (pattern.velocity.length() > 0)
            pattern.velocity.normalize();
        transform.position += pattern.velocity;
    }
}
