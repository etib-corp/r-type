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
        auto &motion = ecs->getComponent<MotionComponent>(entity);

        if (pattern.end_pos == transform.position && pattern.end == DESTROY) {
            ecs->destroyEntity(entity);
        }

        _patterns[pattern.pattern_name](pattern, transform, motion);
    }
}
