/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Engine
*/

#include "Engine.hpp"
#include <iostream>

std::shared_ptr<LE::Engine> LE::Engine::_instance = std::make_shared<LE::Engine>();

LE::Engine::Engine()
{
}

LE::Engine::~Engine()
{
}

std::shared_ptr<LE::Engine> LE::Engine::getInstance()
{
    return _instance;
}

void LE::Engine::run(bool throwError)
{
    // Implementation of the run method
    if (throwError) {
        throw EngineError("An error occurred while running the engine.");
    }
    // Additional logic for running the engine
}

void LE::Engine::runWithDebug()
{
    // Implementation of the runWithDebug method
    // Additional logic for running the engine with debug information
}

void LE::Engine::debug(const std::string& message)
{
    // Implementation of the debug method
    std::cout << "DEBUG: " << message << std::endl;
}