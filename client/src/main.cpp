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

#include "PackUnpack.hpp"
#include "ECS/Ecs.hpp"

class GameScene : public LE::Scene
{
public:
    GameScene() : LE::Scene()
    {
        _eventManager->addEventListener({LE::Input::MOUSE, LE_MOUSE_BUTTON_LEFT, LE::Type::PRESSED}, [this](LE::Engine *engine)
                                        { std::cout << "Left click pressed" << std::endl; });
        _eventManager->addEventListener({LE::Input::MOUSE, LE_MOUSE_BUTTON_LEFT, LE::Type::RELEASED}, [this](LE::Engine *engine)
                                        { std::cout << "Left click released" << std::endl; });
    }
    void play() override
    {
        // std::cout << "Game scene updated." << std::endl;
        _eventManager->pollEvents();
    }
    void stop() override
    {
        std::cout << "Game scene ended." << std::endl;
    }
};

struct Position
{
    float x;
    float y;
};

#include "GUI/Text.hpp"
#include "GUI/Button.hpp"


int main(int ac, char **av)
{
    // Initialize the engine
    auto engine = LE::Engine::getInstance();

    auto scene = std::make_shared<GameScene>();

    engine->addScene("main", scene);
    // Run the engine
    try {
        engine->runWithDebug(); // Change to true to simulate an error
    } catch (const LE::Engine::EngineError &e) {
        std::cerr << "Engine error: " << e.what() << std::endl;
    }
    return 0;
}
