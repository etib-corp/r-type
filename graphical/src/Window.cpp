/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Window
*/

#include "Window.hpp"

#include "Engine.hpp"

LE::Window::Window(const std::string& title, std::size_t width, std::size_t height)
    : _title(title), _width(width), _height(height), _window(nullptr), _framerateLimit(60), _monitor(nullptr), _mode(nullptr) {
    _initGLFW();

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

    if (!_window)
        throw WindowError("Failed to create GLFW window");

    glfwMakeContextCurrent(_window);

    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    glfwSwapInterval(1);
}

LE::Window::~Window()
{
    if (_window)
        glfwDestroyWindow(_window);
    glfwTerminate();
}

void LE::Window::render(std::shared_ptr<LE::Scene> scene)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->draw();
    glfwSwapBuffers(_window);
}

void LE::Window::_initGLFW()
{
    if (!glfwInit())
        throw WindowError("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwSetErrorCallback([](int error, const char* description) {
        std::string errorStr = std::to_string(error);
        throw WindowError("Error |" +  errorStr + "| : \n\t" + description);
    });

    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);


    _monitor = glfwGetPrimaryMonitor();
    _mode = glfwGetVideoMode(_monitor);
}