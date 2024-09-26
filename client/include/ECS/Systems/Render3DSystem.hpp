/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Render3DSystem
*/

#ifndef RENDER3DSYSTEM_HPP_
#define RENDER3DSYSTEM_HPP_

#include "ECS/SystemManager.hpp"
#include "ECS/Components/ModelComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"

class Render3DSystem : public System {
    public:
        Render3DSystem();
        ~Render3DSystem();
        
        void update(Ecs *ecs, float dt);

    protected:
    private:
};

#endif /* !RENDER3DSYSTEM_HPP_ */
