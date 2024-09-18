/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** main
*/

#include "Engine.hpp"

int main()
{
    LE::Engine *engine = LE::Engine::getInstance();
    engine->runWithDebug();
    return 0;
}