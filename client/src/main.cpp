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
        GameScene() : LE::Scene()
        {
            _eventManager->addEventListener({LE::Input::MOUSE, LE_MOUSE_BUTTON_LEFT, LE::Type::PRESSED}, [this](LE::Engine *engine) {
                std::cout << "Left click pressed" << std::endl;
            });
            _eventManager->addEventListener({LE::Input::MOUSE, LE_MOUSE_BUTTON_LEFT, LE::Type::RELEASED}, [this](LE::Engine *engine) {
                std::cout << "Left click released" << std::endl;
            });
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

int main(int ac, char **av)
{
    // Initialize the engine
    auto engine = LE::Engine::getInstance();
    auto scene = std::make_shared<GameScene>();
    engine->addScene("game", scene);
    engine->run(true);
    return 0;
}

/*
#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"

int main1(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();

    try {
        LoaderLib lb(pathLib, "");

        lb.LoadModule();

        IClient *client = lb.createClient();

        client->connectToServer("127.0.0.1", 8080);
        client->sendTCP("Hello from client TCP\n");
        client->sendUDP("Hello from client UDP\n");
        while (true)
        {
        }

    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
*/