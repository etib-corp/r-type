/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** main
*/

#include "Engine.hpp"
#include <iostream>
#include "Rtype.hpp"

int main(void)
{
    auto engine = LE::Engine::getInstance();
    auto game  = std::make_shared<Rtype>();

    game->init();
    engine->setGame(game);
    try {
        engine->runWithDebug(); // Change to true to simulate an error
    } catch (const LE::Engine::EngineError &e) {
        std::cerr << "Engine error: " << e.what() << std::endl;
    }
    return 0;
}
