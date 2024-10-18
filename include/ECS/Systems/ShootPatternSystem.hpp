/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ShootPatternSystem
*/

#pragma once

#include "ECS/Systems/System.hpp"
#include "ECS/Components/ShootPatternComponent.hpp"

class ShootPatternSystem : public System {
    public:
        ShootPatternSystem();
        ~ShootPatternSystem();

        void update(Ecs *ecs, float dt) override;
}