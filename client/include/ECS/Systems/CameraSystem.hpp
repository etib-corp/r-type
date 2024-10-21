/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** CameraSystem
*/

#ifndef CAMERASYSTEM_HPP_
#define CAMERASYSTEM_HPP_

#include "ECS/Components/CameraComponent.hpp"
#include "ECS/SystemManager.hpp"

class CameraSystem : public System {
    public:
        CameraSystem();
        ~CameraSystem();

        void update(Ecs *ecs, float dt) override;

    protected:
    private:
};

#endif /* !CAMERASYSTEM_HPP_ */
