/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Engine
*/

#include "Engine.hpp"
#include "Window.hpp"
#include "globalLogger.hpp"
#include "Shapes/Triangle.hpp"
// #include "GUI/Container.hpp"
// #include "GUI/Interactable.hpp"
#include "GUI/TextField.hpp"
#include "GUI/Button.hpp"

#include <iostream>

LE::Engine *LE::Engine::_instance{nullptr};

LE::Engine::Engine()
{
    _debugMode = false;
    _throwError = false;
    _window = std::make_shared<LE::Window>("The R-Type");
    _clock = std::make_unique<LE::Clock>();
    _framerateLimit = 60; // _window->_defaultFramerate;
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

    if (_configFunc) {
        _configFunc();
        std::cout << "Config function called" << std::endl;
    }
    Color color;
    color._a = 255.0f;
    color._r = 255.0f;
    color._g = 255.0f;
    color._b = 255.0f;
    _window->setClearColor(color);
    while (_window->isOpen()) {
        if (_loopFunc) {
            _loopFunc();
        }
        _game->update();
        _dt = _clock->getElapsedTime();
        if (_clock->getElapsedTime() < (1000.0f / _framerateLimit))
            continue;
        _clock->restart();
        _window->render(_game->_sceneManager->getCurrentScene());
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
        rtypeLog->log<LogType::DEBUG, &std::cout>("DEBUG: {}", message);
    }
}

void LE::Engine::setGame(const std::shared_ptr<LE::Game> game)
{
    _game = game;
}

std::shared_ptr<LE::Game> LE::Engine::getGame()
{
    return _game;
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

void LE::Engine::setLoop(std::function<void()> func)
{
    _loopFunc = func;
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

float LE::Engine::getDeltaTime() const
{
    return _dt;
}

void LE::Engine::restartClock(void)
{
    _clock->restart();
}
