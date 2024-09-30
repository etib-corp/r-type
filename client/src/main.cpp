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

#include "GUI/Text.hpp"

class MyContainer : public LE::GUI::Container {
    public:
        MyContainer() {
            _width = 500;
            _height = 100;
            _x = 0.0;
            _y = 0;

            LE::GUI::Text *text = new LE::GUI::Text(85, "assets/fonts/ARIAL.TTF", 24, "Hello World !");

            addChildren(text);
        }

        ~MyContainer() {
            delete _background;
        }
};

class MyScene : public LE::Scene {
    public:
        MyScene() {
            _guiManager = std::make_shared<LE::GUI::Manager>(800, 600);

            auto container = new MyContainer();

            _guiManager->addChildren(container);
        }

        void init() {
            _guiManager->init();
        }

        void draw() {
            _guiManager->draw();
        }

        void play() {
            draw();
        }

        void stop() {
        }
};

int main(int ac, char **av)
{
    // Initialize the engine
    auto engine = LE::Engine::getInstance();

    auto scene = std::make_shared<MyScene>();

    engine->addScene("main", scene);
    // Run the engine
    try {
        engine->runWithDebug(); // Change to true to simulate an error
    } catch (const LE::Engine::EngineError &e) {
        std::cerr << "Engine error: " << e.what() << std::endl;
    }
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