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
    _systemManager = std::make_unique<SystemManager>();
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

void Ecs::update(float dt)
{
    _systemManager->update(this, dt);
}

void Ecs::setCameraEntity(Entity entity)
{
    _cameraEntity = entity;
}

Entity Ecs::getCameraEntity() const
{
    return _cameraEntity;
}

void *Ecs::getScene() const
{
    return _scene;
}

void Ecs::setScene(void *scene)
{
    _scene = scene;
}