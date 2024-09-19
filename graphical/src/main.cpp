/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** main
*/

#include "Engine.hpp"
#include "Scene.hpp"
#include <iostream>

class GameScene : public LE::Scene {
    public:
        GameScene() : LE::Scene() {}
        void play() override
        {
            std::cout << "Game scene updated." << std::endl;
        }
        void stop() override
        {
            std::cout << "Game scene ended." << std::endl;
        }
};

int main()
{
    LE::Engine *engine = LE::Engine::getInstance();
    engine->runWithDebug();
    return 0;
}