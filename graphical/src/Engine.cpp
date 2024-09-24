/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Engine
*/

#include "Engine.hpp"
#include "SceneManager.hpp"
#include <iostream>

LE::Engine *LE::Engine::_instance{nullptr};

LE::Engine::Engine()
{
    _debugMode = false;
    _throwError = false;
    _sceneManager = std::make_shared<SceneManager>();
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
    srand(static_cast<unsigned int>(time(nullptr)));
    _window = std::make_shared<LE::Window>("Game Window", 800, 600);

    if (_configFunc) {
        _configFunc();
    }
    _sceneManager->init();
    while (_window->isOpen()) {
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

void LE::Engine::addScene(std::shared_ptr<Scene> scene, const std::string &sceneName)
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
