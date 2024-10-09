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
#include "GUI/TextField.hpp"

class GameScene : public LE::Scene
{
public:
    GameScene() : LE::Scene()
    {
        _guiManager = std::make_shared<LE::GUI::Manager>(1920, 1080);
        LE::GUI::TextField *textField = new LE::GUI::TextField(100, 100, 200, 200, "Hello", new LE::Color(LE::Color::CHAR, 0, 0, 0, 255), new LE::Color(LE::Color::CHAR, 255, 255, 255, 255));

        _guiManager->addChildren(textField);
    }
    void play() override
    {
        // std::cout << "Game scene updated." << std::endl;
        _guiManager->draw();
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

/*
#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"

// bool deserializeRequest(const char *data, std::size_t length, std::istringstream *request)
// {
//     if (length < sizeof(std::istringstream))
//     {
//         std::cerr << "Erreur: Données reçues trop courtes." << std::endl;
//         return false;
//     }

//     ::memmove(request, data, sizeof(std::istringstream));
//     return true;
// }

static void receiveFromServer( Message *message, ClientBroker *client_broker)
{
    try {
        message = client_broker->getMessage(0, 1);
        std::cout << "Message received from server" << std::endl;
        delete message;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cout << "No message received. Waiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

static void sendToServer(void)
{

}

int main(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
    LoaderLib loader_lib(pathLib, "");
    INetworkModule *network_module = nullptr;
    ClientBroker *client_broker = nullptr;

    try {
        LoaderLib lb(pathLib, "");

        lb.LoadModule();
        std::ostringstream oss;

    message = new Message();

    Body bodyTest = {._buffer = "|test|test|test|test|"};
    message->setAction('D');
    message->setBody(bodyTest);
    while (true)
    {
        client_broker->addMessage(0, 1, message);
        sleep(3);
    }



    // while (true)
    // {
    //     receiveFromServer(message, client_broker);
    // }
    // client_broker->addMessage(0, 1, message);

    return 0;
}
*/