/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Window
*/

#pragma once

namespace LE {
    class Scene;
}

#include "Clock.hpp"
#include "Error.hpp"
#include "Color.hpp"

#include <cmath>
#include <memory>
#include <string>

#ifdef __linux__
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
#endif

#ifdef __APPLE__
    #define GL_GLEXT_PROTOTYPES
    #include <OpenGL/gl.h>
    #include <OpenGL/glext.h>
#endif

#ifdef _WIN32
    #define GL_GLEXT_PROTOTYPES
    #include <windows.h>
    #include <GL/gl.h>
    #include "GLFW/glext.h"
#endif

#include "GLFW/glfw3.h"
#include "MacGL.hpp"

namespace LE {
    class Shader;
    namespace Shapes {
        class Triangle;
    }
    namespace GUI {
        class Text;
    }
}

extern LE::Shader *fontShader;
extern LE::Shader *triangleShader;

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
            Window(const std::string& title);

            /**
             * @brief Destructor for the Window object.
             */
            ~Window();

            /**
             * @brief Renders the specified scene in the window.
             *
             * @param scene A shared pointer to the scene to be rendered.
             */
            void render(std::shared_ptr<Scene> scene);

            /**
             * @brief Checks if the window is open.
             *
             * @return True if the window is open, false otherwise.
             */
            bool isOpen();

            /**
             * @brief Close the window.
             */
            void close();

            /**
             * @brief Clears the window to the specified color.
             *
             * @param color The color to clear the window to (default is black).
             */
            void clear();

            /**
             * @brief Sets the clear color for the window.
             *
             * @param color The color to set as the clear color.
             */
            void setClearColor(const Color &color);

            /**
             * @brief Gets the GLFW window pointer.
             *
             * @return The GLFW window pointer.
             */
            GLFWwindow* getWindow();

            /**
             * @brief Gets the width of the window.
             *
             * @return The width of the window.
             */
            std::size_t getWidth() const;

            /**
             * @brief Gets the height of the window.
             *
             * @return The height of the window.
             */
            std::size_t getHeight() const;
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
            GLFWmonitor* _monitor;              ///< Pointer to the monitor.
            const GLFWvidmode* _mode;           ///< Pointer to the video mode.
            std::size_t _defaultFramerate;      ///< The default framerate.
            friend class EventManager;          ///< Friend class EventManager.
            friend class Engine;                ///< Friend class Engine.
            friend class LE::Shapes::Triangle;  ///< Friend class LE::Shapes::Triangle.
            friend class LE::GUI::Text;         ///< Friend class LE::GUI::Text.
    };
}
