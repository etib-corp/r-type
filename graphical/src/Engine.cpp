/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Engine
*/

#include "Engine.hpp"
#include <iostream>

LE::Engine *LE::Engine::_instance{nullptr};

LE::Engine::Engine()
{
    _debugMode = false;
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
    srand(static_cast<unsigned int>(time(nullptr)));
    debug("Initializing engine...");
    _window = std::make_shared<LE::Window>("Game Window", 800, 600);
    debug("Window created successfully.");
    _sceneManager = std::make_shared<LE::SceneManager>();
    debug("Scene manager initialized.");
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