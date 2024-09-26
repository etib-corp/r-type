/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Render2DSystem
*/

#ifndef RENDER2DSYSTEM_HPP_
#define RENDER2DSYSTEM_HPP_

#include "ECS/SystemManager.hpp"
#include "ECS/Components/SpriteComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"

class Render2DSystem : public System {
    public:
        Render2DSystem();
        ~Render2DSystem();

        void update(Ecs *ecs, float delta);

    protected:
    private:
        std::shared_ptr<LE::Shader> _shader;
};

#endif /* !RENDER2DSYSTEM_HPP_ */
