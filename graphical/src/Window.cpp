/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Window
*/

#include "Window.hpp"
#include "Shader.hpp"

LE::Shader *fontShader{nullptr};

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

    _clock = std::make_unique<LE::Clock>();
    fontShader = new LE::Shader("assets/shaders/font.vert", "assets/shaders/font.frag");
    fontShader->use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    glUniformMatrix4fv(glGetUniformLocation(fontShader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // glewExperimental = GL_TRUE;
    // if (!glewInit())
    //     throw WindowError("Failed to initialize GLEW");
}

LE::Window::~Window()
{
    if (_window)
        glfwDestroyWindow(_window);
    glfwTerminate();
}

void LE::Window::render(std::shared_ptr<Scene> scene)
{
    if (_clock->getElapsedTime() < (1000.0f / _framerateLimit))
        return;
    _clock->restart();
    clear();
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

bool LE::Window::isOpen()
{
    return !glfwWindowShouldClose(_window);
}

void LE::Window::close()
{
    glfwSetWindowShouldClose(_window, GLFW_TRUE);
}

void LE::Window::setFramerateLimit(std::size_t limit)
{
    _framerateLimit = limit;
}

void LE::Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LE::Window::setClearColor(Color color)
{
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a);
}