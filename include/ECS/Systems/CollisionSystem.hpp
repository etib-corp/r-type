/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "ECS/SystemManager.hpp"
#include "ECS/Components/HurtBoxComponent.hpp"
#include "ECS/Components/HitBoxComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "Shapes/Rectangle.hpp"

class CollisionSystem : public System {
    public:
        CollisionSystem();
        ~CollisionSystem();

        void update(Ecs *ecs, float dt) override;

    protected:
        std::unique_ptr<LE::Shapes::Rectangle> _rectangle;
    private:
};

#endif /* !COLLISIONSYSTEM_HPP_ */
