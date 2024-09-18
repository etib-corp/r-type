/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include <iostream>
#include "Engine.hpp"

int main(int ac, char **av)
{
    // Initialize the engine
    auto engine = LE::Engine::getInstance();

    // Run the engine
    try {
        engine->runWithDebug(); // Change to true to simulate an error
    } catch (const LE::Engine::EngineError &e) {
        std::cerr << "Engine error: " << e.what() << std::endl;
    }
    return 0;
}