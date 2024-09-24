/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** EntityManager
*/

#include "ECS/EntityManager.hpp"

EntityManager::EntityManager()
{
    _livingEntityCount = 0;
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        _availableEntities.push(entity);
    }
}

EntityManager::~EntityManager()
{
}

Entity EntityManager::createEntity(void)
{
    if (_livingEntityCount >= MAX_ENTITIES) {
        throw EntityManagerError("Maximum number of entities reached");
    }
    Entity entity = _availableEntities.front();
    _availableEntities.pop();
    _livingEntityCount++;
    return entity;
}

void EntityManager::destroyEntity(Entity entity)
{
    if (entity >= MAX_ENTITIES || entity < 0) {
        throw EntityManagerError("Entity out of range");
    }
    _availableEntities.push(entity);
    _signatures[entity] = 0;
    _livingEntityCount--;
}

void EntityManager::setSignature(Entity entity, Signature signature)
{
    if (entity >= MAX_ENTITIES || entity < 0) {
        throw EntityManagerError("Entity out of range");
    }
    _signatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
    if (entity >= MAX_ENTITIES || entity < 0) {
        throw EntityManagerError("Entity out of range");
    }
    return _signatures[entity];
}