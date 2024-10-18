/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ShootPatternSystem
*/

#pragma once

#include "ECS/SystemManager.hpp"
#include "ECS/Components/ShootPatternComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/MotionComponent.hpp"

class ShootPatternSystem : public System {
    public:
        ShootPatternSystem();
        ~ShootPatternSystem();

        void update(Ecs *ecs, float dt) override;

    protected:
};
