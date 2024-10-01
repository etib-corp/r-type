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
#include "GUI/Button.hpp"

class MyContainer : public LE::GUI::Container {
    public:
        MyContainer(const std::string &content) {
            _width = 500;
            _height = 100;
            _x = 0.0;
            _y = 0;

            LE::GUI::Text *text = new LE::GUI::Text(85, "assets/fonts/ARIAL.TTF", 24, content);

            addChildren(text);
        }

        ~MyContainer() {
            delete _background;
        }
};

class MyParentContainer : public LE::GUI::Container {
    public:
        MyParentContainer() {
            _width = 500;
            _height = 100;
            _x = 100.0;
            _y = 200;

            auto firstSubContainer = new MyContainer("Hello World !");
            auto secondSubContainer = new LE::GUI::Button(0, 200, 500, 100, "Click me !", new LE::Color(LE::Color::CHAR, 0, 0, 255, 255), new LE::Color(LE::Color::CHAR, 255, 255, 255, 255));

            // addChildren(firstSubContainer);
            addChildren(secondSubContainer);
        }

        ~MyParentContainer() {
            delete _background;
        }
};

class MyScene : public LE::Scene {
    public:
        MyScene() {
            _guiManager = std::make_shared<LE::GUI::Manager>(1920, 1080);

            auto container = new MyParentContainer();

            _guiManager->addChildren(container);
            _eventManager = std::make_shared<LE::EventManager>();
        }

        void init() {
            _guiManager->init();
        }

        void draw() {
            _eventManager->pollEvents();
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
    LoaderLib loader_lib(pathLib, "");
    INetworkModule *network_module = nullptr;
    ClientBroker *client_broker = nullptr;

    try {
        LoaderLib lb(pathLib, "");

        lb.LoadModule();
        std::ostringstream oss;

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