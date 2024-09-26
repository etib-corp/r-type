/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Render3DSystem
*/

#include "ECS/Systems/Render3DSystem.hpp"
#include "ECS/Ecs.hpp"

Render3DSystem::Render3DSystem()
{
}

Render3DSystem::~Render3DSystem()
{
}

void Render3DSystem::update(Ecs *ecs, float dt)
{
    for (auto &entity : _entities) {
        auto &render3D = ecs->getComponent<ModelComponent>(entity);
        auto &transform = ecs->getComponent<TransformComponent>(entity);
        // auto &camera = ecs->getComponent<CameraComponent>(entity);
    }
}