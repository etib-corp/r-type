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
<<<<<<< HEAD
#include "GUI/TextField.hpp"
=======
#include "EnumClass.hpp"
>>>>>>> 897bf4002 (Chlore: add examples request on the client)

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
    UpdateEcs updateEcs = {0};
    try {
        message = client_broker->getMessage(0, 1);
        if (message == nullptr)
            return;
        std::cout << "Message received from server" << std::endl;
        // std::cout << message->getBody()._buffer << std::endl;
        ::memmove(&updateEcs, message->getBody()._buffer, sizeof(UpdateEcs));
        std::cout << (int)updateEcs.ecs_id << std::endl;
        std::cout << (int)updateEcs.actionInput << std::endl;
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

static void sendAuthToServer(ClientBroker *client_broker, std::string playerName)
{
    Message *message = new Message();
    Body body;

    ::memmove(body._buffer, playerName.c_str(), playerName.size() + 1);
    message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
    message->setAction(static_cast<uint8_t>(ActionCode::USERNAME));
    message->setBody(body);
    client_broker->addMessage(0, 1, message);
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
    std::string name = "mannuuuuuuuuuu";

    sendAuthToServer(client_broker, name);

    Body bodyTest = {._buffer = "|test|test|test|test|"};
    message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
    message->setAction(static_cast<uint8_t>(ActionCode::UP));
    message->setBody(bodyTest);
    client_broker->addMessage(0, 1, message);
    sleep(3);
    message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
    message->setAction(static_cast<uint8_t>(ActionCode::DOWN));
    message->setBody(bodyTest);
    client_broker->addMessage(0, 1, message);
    sleep(3);
    message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
    message->setAction(static_cast<uint8_t>(ActionCode::LEFT));
    message->setBody(bodyTest);
    client_broker->addMessage(0, 1, message);
    sleep(3);
    message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
    message->setAction(static_cast<uint8_t>(ActionCode::RIGHT));
    message->setBody(bodyTest);
    client_broker->addMessage(0, 1, message);
    sleep(3);
    while (true)
    {
        receiveFromServer(message, client_broker);
    }
    // client_broker->addMessage(0, 1, message);

    return 0;
}
*/