/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Window
*/

#pragma once

#include "Clock.hpp"
#include "Error.hpp"
#include "Scene.hpp"

#include <cmath>
#include <memory>
#include <string>
#include <GLFW/glfw3.h>

/**
 * @file Window.hpp
 * @brief Defines the Window class.
 */
namespace LE {
    /**
     * @class Window
     * @brief The Window class is responsible for creating and managing a graphical window.
     *
     * The Window class provides functionalities for rendering scenes and handling window events.
     */
    class Window {
        public:
            /**
             * @class WindowError
             * @brief Exception class for window-related errors.
             *
             * This class is used to represent errors that occur within the Window class.
             */
            class WindowError : public Error {
                public:
                    /**
                     * @brief Constructs a WindowError object with the specified error message.
                     *
                     * @param message The error message.
                     */
                    WindowError(const std::string& message) : Error(message) {}
            };

            /**
             * @brief Constructs a Window object with the specified title, width, and height.
             *
             * @param title The title of the window.
             * @param width The width of the window.
             * @param height The height of the window.
             */
            Window(const std::string& title, std::size_t width, std::size_t height);

            /**
             * @brief Destructor for the Window object.
             */
            ~Window();

            /**
             * @brief Renders the specified scene in the window.
             *
             * @param scene A shared pointer to the scene to be rendered.
             */
            void render(std::shared_ptr<LE::Scene> scene);
        private:

            /**
             * @brief Initializes GLFW and creates a window.
             *
             * @throws WindowError if window creation fails.
             */
            void _initGLFW();

            std::size_t _width;                 ///< The width of the window.
            std::size_t _height;                ///< The height of the window.
            std::string _title;                 ///< The title of the window.
            GLFWwindow* _window;                ///< Pointer to the GLFW window.
            std::size_t _framerateLimit;        ///< The frame rate limit.
            GLFWmonitor* _monitor;              ///< Pointer to the monitor.
            const GLFWvidmode* _mode;           ///< Pointer to the video mode.
            std::unique_ptr<Clock> _clock;      ///< Unique pointer to the Clock object.
    };
}