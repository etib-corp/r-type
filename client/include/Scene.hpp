/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Scene
*/

#pragma once

#include <memory>

#include "Error.hpp"
#include "GUI/Manager.hpp"
#include "EventManager.hpp"

/**
 * @file Scene.hpp
 * @brief Defines the Scene class and its associated error handling.
 */

namespace LE {
    /**
     * @class Scene
     * @brief Abstract base class representing a scene in the graphical system.
     *
     * The Scene class provides an interface for managing scenes, including
     * playing and stopping them. It also includes error handling specific
     * to scenes.
     */
    class Scene {
        public:
            /**
             * @class SceneError
             * @brief Exception class for scene-related errors.
             *
             * This class is used to represent errors that occur within the
             * Scene class. It inherits from the base Error class.
             */
            class SceneError : public Error {
                public:
                    /**
                     * @brief Constructor for SceneError.
                     * @param message The error message.
                     */
                    SceneError(const std::string &message) : Error(message) {}
            };

            /**
             * @brief Default constructor for Scene.
             */
            Scene();

            /**
             * @brief Virtual destructor for Scene.
             */
            virtual ~Scene() = default;

            /**
             * @brief Pure virtual function to play the scene.
             *
             * This function must be implemented by derived classes to define
             * the behavior when the scene is played.
             */
            virtual void play() = 0;

            /**
             * @brief Pure virtual function to draw the scene.
             *
             * This function must be implemented by derived classes to define
             * how the scene is rendered.
             */
            void draw();

            /**
             * @brief Pure virtual function to stop the scene.
             *
             * This function must be implemented by derived classes to define
             * the behavior when the scene is stopped.
             */
            virtual void stop() = 0;

            virtual void init() = 0;

            /**
             * @brief Shared pointer to an ECS (Entity Component System) instance.
             *
             * This member variable holds a shared pointer to an ECS instance,
             * which is used to manage entities and components within the scene.
             */
            std::shared_ptr<void *> _ecs;
            std::shared_ptr<LE::GUI::Manager> _guiManager;      ///< Shared pointer to the GUI Manager instance.
            std::shared_ptr<LE::EventManager> _eventManager;    ///< Shared pointer to the Event Manager instance.
    };
}
