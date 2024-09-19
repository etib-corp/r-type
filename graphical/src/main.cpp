/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** main
*/

#include <iostream>
#include <GL/glut.h>
#include "Engine.hpp"

class MyScene : public LE::Scene {
    public:
        MyScene() {
            // Initialize GUI Manager
            _guiManager = std::make_shared<LE::GUI::Manager>(800, 600);
        }

        void play() override {}

        void stop() override {}

};

int main(int ac, char **av)
{
    // Initialize the engine
    glutInit(&ac, av);
    auto engine = LE::Engine::getInstance();
    auto scene = std::make_shared<MyScene>();

    // Add the scene to the engine
    engine->addScene(scene, "GUI");
    // Run the engine
    try {
        engine->runWithDebug(); // Change to true to simulate an error
    } catch (const LE::Engine::EngineError &e) {
        std::cerr << "Engine error: " << e.what() << std::endl;
    }
    return 0;
}