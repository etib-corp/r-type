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

        motion.velocity = {0, 0, 0};

        motion.velocity.x = (motion.movement[MOVEMENT_RIGHT] - motion.movement[MOVEMENT_LEFT]);
        motion.velocity.y = (motion.movement[MOVEMENT_UP] - motion.movement[MOVEMENT_DOWN]);
        // if (motion.velocity.length() > 0)
        //     motion.velocity.normalize();
        transform.position += motion.velocity;
    }
}
