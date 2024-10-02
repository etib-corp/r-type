/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Render3DSystem
*/

#pragma once

#include "ECS/SystemManager.hpp"
#include "ECS/Components/ModelComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"


class Render3DSystem : public System {
    public:
        Render3DSystem();

        ~Render3DSystem();

        void update(Ecs *ecs, float delta);
    private:
        std::shared_ptr<LE::Shader> _shader;
};