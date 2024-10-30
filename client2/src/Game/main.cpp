/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** main
*/

#include "interface/IEngine.hpp"
#include <iostream>
#include "Game/Rtype.hpp"

int main(void)
{
    LE::GraphicalLib lib("/home/julithein/delivery/tek3/r-type/build/dependencies/lion-engine/liblion-engine.so");
    std::shared_ptr<LE::IEngine> engine = lib.createEngine();
    engine->init();
    engine->setFramerateLimit(60);

    engine->setGame<Rtype>();

    engine->run();
    return 0;
}
