/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Engine
*/

#pragma once

#include <memory>
#include <iostream>

#include "SceneManager.hpp"
#include "Window.hpp"
#include "Game.hpp"
#include "Error.hpp"
#include "ECS/Components/CameraComponent.hpp"

namespace LE {
    class Window;
    class SceneManager;
    class Game;

    namespace Shapes {
        class Triangle;
    }
    namespace GUI {
        class Text;
        class Interactable;
        class Button;
        class TextField;
    }
}

/**
 * @file Engine.hpp
 * @brief Defines the Engine class.
 */

namespace LE {
    /**
     * @class Engine
     * @brief The Engine class is responsible for managing the game engine's core functionalities.
     *
     * The Engine class is a singleton, ensuring that only one instance of the engine exists throughout the application.
     */
    class Engine {
        public:
            /**
             * @class EngineError
             * @brief The EngineError class represents an exception that can be thrown in the Engine class.
             *
             * This class inherits from the base Error class and is used to handle engine-specific errors.
             */
            class EngineError : public Error {
                public:
                    /**
                     * @brief Constructs an EngineError object with the specified error message.
                     *
                     * @param message The error message.
                     */
                    EngineError(const std::string& message) : Error(message) {}
            };
            /**
             * @brief Deleted copy constructor for the Engine class.
             */
            Engine(const Engine& engine) = delete;

            /**
             * @brief Deleted assignment operator for the Engine class.
             */
            Engine& operator=(const Engine& engine) = delete;

            /**
             * @brief Gets the singleton instance of the Engine class.
             *
             * @return A shared pointer to the Engine instance.
             */
            static Engine *getInstance();

            /**
             * @brief Runs the engine.
             *
             * @param throwError A boolean flag indicating whether to throw an error.
             */
            void run(bool throwError = false);

            /**
             * @brief Runs the engine with debug information.
             */
            void runWithDebug();

            /**
             * @brief Outputs debug information.
             *
             * @param message The debug message to output.
             */
            void debug(const std::string& message);

            /**
             * @brief Adds a scene to the engine.
             *
             * @param scene A shared pointer to the scene to add.
             */
            void setGame(const std::shared_ptr<LE::Game> game);

            /**
             * @brief Removes a scene from the engine.
             *
             * @return A shared pointer to the scene that was removed.
             */
            std::shared_ptr<LE::Game> getGame();

            /**
             * @brief Throws an error.
             *
             * @param error The error to throw.
             * @note This function is use to throw an error from the Engine class only if the throwError flag is set to true.
             */
            void throwError(const LE::Error& error);

            /**
             * @brief Sets the configuration function.
             *
             * This function is used to set a configuration function that will be called before the engine starts running.
             *
             * @param func The configuration function to set.
             */
            void setConfig(std::function<void()> func);

            /**
             * @brief Sets the loop function.
             *
             * This function is used to set a loop function that will be called during the engine's main loop.
             *
             * @param func The loop function to set.
             */
            void setLoop(std::function<void()> func);

            /**
             * @brief Sets the frame rate limit for the window.
             *
             * @param limit The frame rate limit.
             */
            void setFramerateLimit(std::size_t limit);

            /**
             * @brief Gets the width of the window.
             *
             * @return The width of the window.
             */
            std::size_t getWindowWidth() const;

            /**
             * @brief Gets the height of the window.
             *
             * @return The height of the window.
             */
            std::size_t getWindowHeight() const;

            float getDeltaTime() const;

        private:
            /**
             * @brief Private constructor for the Engine class.
             */
            Engine();

            /**
             * @brief Destructor for the Engine class.
             */
            ~Engine();

            static Engine* _instance; ///< The singleton instance of the Engine class.

            std::shared_ptr<LE::Window> _window;            ///< Shared pointer to the Window instance.
            std::shared_ptr<LE::Game> _game;                ///< Shared pointer to the Game instance.
            bool _debugMode;                                ///< Flag indicating whether debug mode is enabled.
            bool _throwError;                               ///< Flag indicating whether to throw an error.
            std::function<void ()> _configFunc;             ///< Configuration function. This function is called before the engine starts running.
            std::function<void ()> _loopFunc;               ///< Loop function. This function is called during the engine's main loop.
            std::unique_ptr<Clock> _clock;                  ///< Unique pointer to the Clock object.
            float _dt;                                      ///< The delta time.
            std::size_t _framerateLimit;                    ///< The frame rate limit.
            friend class EventManager;                      ///< Friend class EventManager.
            friend class LE::Shapes::Triangle;              ///< Friend class LE::Shapes::Triangle.
            friend class LE::GUI::Text;                     ///< Friend class LE::GUI::Text.
            friend class LE::GUI::Interactable;             ///< Friend class LE::GUI::Interactable.
            friend class LE::GUI::Button;                   ///< Friend class LE::GUI::Button.
            friend class LE::GUI::Container;                ///< Friend class LE::GUI::Container.
            friend class LE::GUI::TextField;                ///< Friend class LE::GUI::TextField.
    };
}