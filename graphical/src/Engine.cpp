/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Engine
*/

#include "Engine.hpp"

LE::Engine *LE::Engine::_instance{nullptr};

LE::Engine::Engine()
{
    _debugMode = false;
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
    srand(static_cast<unsigned int>(time(nullptr)));
    debug("Initializing engine...");
    _window = std::make_shared<LE::Window>("Game Window", 800, 600);
    debug("Window created successfully.");
    debug("Running engine...");
    while (_window->isOpen()) {
        debug("Engine running...");
        _sceneManager->play();
        debug("Scene playing...");
        _window->render(_sceneManager->getCurrentScene());
        debug("Scene rendered...");
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
