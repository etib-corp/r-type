/*
** EPITECH PROJECT, 2024
** client
** File description:
** Ecs
*/

#include "ECS/Ecs.hpp"

Ecs::Ecs()
{
    _componentManager = std::make_unique<ComponentManager>();
    _entityManager = std::make_unique<EntityManager>();
}

Ecs::~Ecs()
{
}

Entity Ecs::createEntity()
{
    return _entityManager->createEntity();
}

Entity Ecs::createEntity(Entity entity)
{
    return _entityManager->createEntity(entity);
}

void Ecs::destroyEntity(Entity entity)
{
    _entityManager->destroyEntity(entity);
    _componentManager->entityDestroyed(entity);
}