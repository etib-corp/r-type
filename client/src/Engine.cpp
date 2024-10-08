/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Engine
*/

#include "Engine.hpp"
#include "SceneManager.hpp"
#include "Window.hpp"
#include <iostream>

LE::Engine *LE::Engine::_instance{nullptr};

LE::Engine::Engine()
{
    _debugMode = false;
    _throwError = false;
    _window = std::make_shared<LE::Window>("The R-Type");
    _sceneManager = std::make_shared<SceneManager>();
    _clock = std::make_unique<LE::Clock>();
    _framerateLimit = _window->_defaultFramerate;
}

LE::Engine::~Engine()
{
}

LE::Engine* LE::Engine::getInstance()
{
    if (!_instance) {
        _instance = new Engine();
    }
    return _instance;
}

void LE::Engine::run(bool throwError)
{
    _throwError = throwError;

    std::cout << "Engine running." << std::endl;
    if (_configFunc) {
        _configFunc();
    }
    Color color;
    color.a = 255;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    _window->setClearColor(color);
    _sceneManager->init();
    while (_window->isOpen()) {
        _dt = _clock->getElapsedTime();
        if (_clock->getElapsedTime() < (1000.0f / _framerateLimit))
            continue;
        _clock->restart();
        _sceneManager->play();
        _window->render(_sceneManager->getCurrentScene());
    }
}

void LE::Engine::runWithDebug()
{
    _debugMode = true;
    run();
    _debugMode = false;
}

void LE::Engine::debug(const std::string& message)
{
    if (_debugMode) {
        std::cout << "DEBUG: " << message << std::endl;
    }
}

void LE::Engine::addScene(const std::string &sceneName, const std::shared_ptr<Scene> scene)
{
    debug("Adding scene in engine: " + sceneName);
    _sceneManager->addScene(scene, sceneName);
    debug("Scene added in engine: " + sceneName);
}

void LE::Engine::removeScene(const std::string& sceneName)
{
    _sceneManager->removeScene(sceneName);
}

void LE::Engine::throwError(const LE::Error& error)
{
    if (_throwError) {
        throw error;
    }
}

void LE::Engine::setConfig(std::function<void()> func)
{
    _configFunc = func;
}

void LE::Engine::setFramerateLimit(std::size_t limit)
{
    _framerateLimit = limit;
}
std::size_t LE::Engine::getWindowWidth() const
{
    return _window->getWidth();
}

std::size_t LE::Engine::getWindowHeight() const
{
    return _window->getHeight();
}