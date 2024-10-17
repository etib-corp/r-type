/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MoveSystem
*/

#include "ECS/Systems/MoveSystem.hpp"
#include "ECS/Ecs.hpp"

MoveSystem::MoveSystem()
{
}

MoveSystem::~MoveSystem()
{
}

void MoveSystem::update(Ecs *ecs, float delta)
{

    for (auto &entity : _entities) {
        auto &transform = ecs->getComponent<TransformComponent>(entity);
        auto &motion = ecs->getComponent<MotionComponent>(entity);

        transform.position += motion.velocity;
    }
}
