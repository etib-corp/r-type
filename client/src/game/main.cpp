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
    auto scene = std::make_shared<Rtype>();

    engine->addScene("main", scene);
    scene->init();
    try {
        engine->runWithDebug(); // Change to true to simulate an error
    } catch (const LE::Engine::EngineError &e) {
        std::cerr << "Engine error: " << e.what() << std::endl;
    }
    return 0;
}
