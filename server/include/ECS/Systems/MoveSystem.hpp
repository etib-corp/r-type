/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MoveSystem
*/

#ifndef MOVESYSTEM_HPP_
#define MOVESYSTEM_HPP_

#include "ECS/SystemManager.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/MotionComponent.hpp"

class MoveSystem : public System {
    public:
        MoveSystem();
        ~MoveSystem();

        void update(Ecs *ecs, float delta);

    protected:
    private:
};

#endif /* !MOVESYSTEM_HPP_ */
