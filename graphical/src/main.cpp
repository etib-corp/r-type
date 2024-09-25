/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** main
*/

#include <iostream>
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

class MyScene : public LE::Scene {
    public:
        MyScene() {
            // Initialize GUI Manager
            _guiManager = std::make_shared<LE::GUI::Manager>(800, 600);
            _guiManager->addChildren(new LE::GUI::Text(42, "assets/fonts/ARIAL.TTF", 80, "Hello World !"));
        }

        void play() override {
            draw();
        }

        void stop() override {}

};

int main(int ac, char **av)
{
    // Initialize the engine
    // glutInit(&ac, av);
    auto engine = LE::Engine::getInstance();

    std::function f = [&]() {
        auto scene = std::make_shared<MyScene>();

        LE::Engine::getInstance()->addScene(scene, "GUI");
    };

    engine->setConfig(f);
    // Add the scene to the engine
    // Run the engine
    try {
        engine->run(); // Change to true to simulate an error
    } catch (const LE::Engine::EngineError &e) {
        std::cerr << "Engine error: " << e.what() << std::endl;
    }
    return 0;
}