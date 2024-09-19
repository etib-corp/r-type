/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Engine
*/

#pragma once

namespace LE {
    class Window;
    class SceneManager;
}

#include <memory>
#include "Error.hpp"
#include "Window.hpp"

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
             * @brief Throws an error.
             *
             * @param error The error to throw.
             * @note This function is use to throw an error from the Engine class only if the throwError flag is set to true.
             */
            void throwError(const LE::Error& error);
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

            std::shared_ptr<LE::Window> _window; ///< Shared pointer to the Window instance.
            std::shared_ptr<LE::SceneManager> _sceneManager; ///< Shared pointer to the SceneManager instance.
            bool _debugMode; ///< Flag indicating whether debug mode is enabled.
            bool _throwError; ///< Flag indicating whether to throw an error.
            friend class EventManager; ///< Friend class EventManager.
    };
}