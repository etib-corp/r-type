/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <memory>

namespace LE {
    class Scene {
        public:
            virtual ~Scene() = default;

            virtual void play() = 0;
            virtual void stop() = 0;

            std::shared_ptr<void *> _ecs;
    };
}

#endif /* !SCENE_HPP_ */
