/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem
*/

#include "ECS/Systems/CollisionSystem.hpp"
#include "ECS/Ecs.hpp"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(Ecs *ecs, float dt)
{
    std::vector<HurtBox> hurtboxHit;

    for (auto entity : _entities) {
        auto &hitbox = ecs->getComponent<HitBox>(entity);
        auto &transform = ecs->getComponent<TransformComponent>(entity);
        // _rectangle->draw();
        for (auto entity2 : _entities) {
            if (entity == entity2)
                continue;
            auto &hurtbox = ecs->getComponent<HurtBox>(entity2);
            auto &transform2 = ecs->getComponent<TransformComponent>(entity2);
            std::bitset<NB_LAYERS> layers = hurtbox.layers & hitbox.masks;

            if (layers.none())
                continue;

            if (transform.position.x < transform2.position.x + hurtbox.width &&
                transform.position.x + hitbox.width > transform2.position.x &&
                transform.position.y < transform2.position.y + hurtbox.height &&
                transform.position.y + hitbox.height > transform2.position.y) {
                hurtboxHit.push_back(hurtbox);
            }
        }
    }
    for (auto& hurtbox : hurtboxHit) {
        hurtbox.onHit();
    }
}
