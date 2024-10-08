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
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/PatternComponent.hpp"

/**
 * @brief A render 2D system.
 *
 * This system is responsible for rendering 2D entities.
 * It uses a shader to render the entities.
 */
class Render2DSystem : public System {
    public:
        /**
         * @brief Construct a new Render 2D System object
         */
        Render2DSystem();

        /**
         * @brief Destroy the Render 2D System object
         */
        ~Render2DSystem();

        /**
         * @brief Update the system
         *
         * This function will be used to update the system
         * @param ecs The ecs
         * @param delta The delta time
         */
        void update(Ecs *ecs, float delta);

    protected:
    private:
        std::shared_ptr<LE::Shader> _shader;    ///< The shader of the system
};

#endif /* !RENDER2DSYSTEM_HPP_ */
