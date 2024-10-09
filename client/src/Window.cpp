/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Window
*/

#include "Window.hpp"

#include "Scene.hpp"
#include "Shader.hpp"

#include "Shapes/Triangle.hpp"
#include "GUI/Text.hpp"

LE::Shader *fontShader{nullptr};
LE::Shader *triangleShader{nullptr};

LE::Window::Window(const std::string& title)
    : _title(title), _window(nullptr), _monitor(nullptr), _mode(nullptr) {
    _initGLFW();

    _monitor = glfwGetPrimaryMonitor();
    _mode = glfwGetVideoMode(_monitor);
    _width = _mode->width;
    _height = _mode->height;
    _defaultFramerate = _mode->refreshRate;
    std::cout << "Framerate: " <<  _defaultFramerate << std::endl;

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

    if (!_window)
        throw WindowError("Failed to create GLFW window");

    glfwMakeContextCurrent(_window);

    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
    // glFrontFace(GL_CW);

    glfwSwapInterval(1);

    fontShader = new LE::Shader("assets/shaders/font.vert", "assets/shaders/font.frag");
    triangleShader = new Shader("assets/shaders/triangle.vert", "assets/shaders/triangle.frag");
    fontShader->use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(_width), 0.0f, static_cast<float>(_height));
    glUniformMatrix4fv(glGetUniformLocation(fontShader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

LE::Window::~Window()
{
    if (_window)
        glfwDestroyWindow(_window);
    glfwTerminate();
}

void LE::Window::render(std::shared_ptr<Scene> scene)
{
    scene->draw();
    glfwSwapBuffers(_window);
    clear();
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

void LE::Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LE::Window::setClearColor(Color *color)
{
    glClearColor(color->_r, color->_g, color->_b, color->_a);
}

GLFWwindow* LE::Window::getWindow()
{
    return _window;
}

std::size_t LE::Window::getWidth() const
{
    return _width;
}

std::size_t LE::Window::getHeight() const
{
    return _height;
}