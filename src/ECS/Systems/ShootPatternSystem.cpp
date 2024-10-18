/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ShootPatternSystem
*/

#include "ECS/Systems/ShootPatternSystem.hpp"
#include "ECS/Ecs.hpp"

ShootPatternSystem::ShootPatternSystem()
{
}

ShootPatternSystem::~ShootPatternSystem()
{
}

void ShootPatternSystem::update(Ecs *ecs, float dt)
{
    std::vector<Entity> end;
    for (auto &entity : _entities) {
        auto &pattern = ecs->getComponent<ShootPatternComponent>(entity);
        auto &transform = ecs->getComponent<TransformComponent>(entity);
        auto &motion = ecs->getComponent<MotionComponent>(entity);

        if (pattern.end == TIME) {
            pattern.currentTime += dt;
            if (pattern.currentTime >= pattern.time) {
                end.push_back(entity);
            }
        }

        // pattern[pattern.pattern_name](pattern, transform, motion);
    }

    for (auto &entity : end) {
        ecs->removeComponent<ShootPatternComponent>(entity);
    }
}
