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
#include "EnumClass.hpp"
#include "GUI/TextField.hpp"
#include "EnumClass.hpp"
#include <chrono>
#include "etibjson.hpp"

#include "Game/Menu.hpp"

bool parseJsonAndCreateEnemy(std::shared_ptr<Ecs> ecs, std::string path)
{
    JsonParser parser(path);
    if (!parser.parseFile()) {
        std::cerr << parser.getErrorMessage() << std::endl;
        return false;
    }
    auto jsonEnemy = (*parser.getJsonValue())["enemy"];
    if (jsonEnemy == nullptr) {
        std::cerr << "Error: No enemy found in the json file." << std::endl;
        return false;
    }
    for (auto jsonValue : jsonEnemy->getArrayValue()) {
        Entity entity = ecs->createEntity();
        MotionComponent motion = {};
        ModelComponent *model = {};
        auto jsonStartPos = jsonValue->getObjectValue()["start_pos"];
        TransformComponent transform = createTransformComponent(
            LE::Vector3<float>(jsonStartPos->getArrayValue()[0]->getNumberValue(), jsonStartPos->getArrayValue()[1]->getNumberValue(), jsonStartPos->getArrayValue()[2]->getNumberValue()),
            LE::Vector3<float>(jsonValue->getObjectValue()["rotation"]->getArrayValue()[0]->getNumberValue(), jsonValue->getObjectValue()["rotation"]->getArrayValue()[1]->getNumberValue(), jsonValue->getObjectValue()["rotation"]->getArrayValue()[2]->getNumberValue()),
            LE::Vector3<float>(jsonValue->getObjectValue()["scale"]->getNumberValue(), jsonValue->getObjectValue()["scale"]->getNumberValue(), jsonValue->getObjectValue()["scale"]->getNumberValue())
        );
        auto jsonEndPos = jsonValue->getObjectValue()["end_pos"];
        PatternComponent pattern = createPatternComponent(
            jsonValue->getObjectValue()["pattern"]->getStringValue(),
            LE::Vector3<float>(jsonEndPos->getArrayValue()[0]->getNumberValue(), jsonEndPos->getArrayValue()[1]->getNumberValue(), jsonEndPos->getArrayValue()[2]->getNumberValue()),
            jsonValue->getObjectValue()["speed"]->getNumberValue(),
            PatternEnd::STAY
        );
        ecs->addComponent<TransformComponent>(entity, transform);
        ecs->addComponent<PatternComponent>(entity, pattern);
        ecs->addComponent<MotionComponent>(entity, motion);
        model = createModelComponent(jsonValue->getObjectValue()["texture_obj"]->getStringValue());
        ecs->addComponent<ModelComponent>(entity, *model);

    }
    return true;
}

class GameScene : public LE::Scene
{
public:
    GameScene() : LE::Scene()
    {
        _eventManager->addEventListener({LE::Input::MOUSE, LE_MOUSE_BUTTON_LEFT, LE::Type::PRESSED}, [this](LE::Engine *engine, float dt)
                                        { std::cout << "Left click pressed" << std::endl; });
        _eventManager->addEventListener({LE::Input::MOUSE, LE_MOUSE_BUTTON_LEFT, LE::Type::RELEASED}, [this](LE::Engine *engine, float dt)
                                        { std::cout << "Left click released" << std::endl; });
        _guiManager = std::make_shared<LE::GUI::Manager>(1920, 1080);
        LE::GUI::TextField *textField = new LE::GUI::TextField(100, 100, 200, 200, "Hello", new LE::Color(LE::Color::CHAR, 0, 0, 0, 255), new LE::Color(LE::Color::CHAR, 255, 255, 255, 255));

        _guiManager->addChildren(textField);
    }
};

struct Position
{
    float x;
    float y;
};

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
            _y = 0;

            auto firstSubContainer = new MyContainer("Hello World !");
            auto secondSubContainer = new MyContainer("Hi Marvin !");

            addChildren(firstSubContainer);
            addChildren(secondSubContainer);
        }

        ~MyParentContainer() {
            delete _background;
        }
};

int _main(int ac, char **av)
{
    // Initialize the engine
    auto engine = LE::Engine::getInstance();

    // auto scene = std::make_shared<GameScene>();

    // engine->addScene("main", scene);

    // engine->addScene("menu", std::make_shared<Menu>());
    // Run the engine
    try {
        engine->runWithDebug(); // Change to true to simulate an error
    } catch (const LE::Engine::EngineError &e) {
        std::cerr << "Engine error: " << e.what() << std::endl;
    }
    return 0;
}
#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"
#include "interface/INetworkModule/INetworkModule.hpp"
#include <cstring>
#include <sstream>
#include "PackUnpack.hpp"
#include "message/ClientBroker.hpp"
#include <EnumClass.hpp>
#include "Common.hpp"

static void receiveFromServer( Message *message, ClientBroker *client_broker)
{
    UpdateEcs updateEcs = {0};
    try {
        message = client_broker->getMessage(0, 1);
        if (message == nullptr)
            return;
        std::cout << "Message received from server" << std::endl;
        ::memmove(&updateEcs, message->getBody()._buffer, sizeof(UpdateEcs));
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

int main_(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
    LoaderLib loader_lib(pathLib, "");
    INetworkModule *network_module = nullptr;
    ClientBroker *client_broker = nullptr;

    loader_lib.LoadModule();
    network_module = loader_lib.createNetworkModule();
    client_broker = new ClientBroker(network_module, "127.0.0.1", 8080);

    Message *message = nullptr;

    message = new Message();
    std::string name = "mannuuuuuuuuuu";

    sendAuthToServer(client_broker, name);

    Body bodyTest = {._buffer = "|test|test|test|test|"};
    message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
    message->setAction(static_cast<uint8_t>(ActionCode::UP));
    message->setBody(bodyTest);
    client_broker->addMessage(0, 1, message);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
    message->setAction(static_cast<uint8_t>(ActionCode::DOWN));
    message->setBody(bodyTest);
    client_broker->addMessage(0, 1, message);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
    message->setAction(static_cast<uint8_t>(ActionCode::LEFT));
    message->setBody(bodyTest);
    client_broker->addMessage(0, 1, message);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
    message->setAction(static_cast<uint8_t>(ActionCode::RIGHT));
    message->setBody(bodyTest);
    client_broker->addMessage(0, 1, message);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while (true)
    {
        receiveFromServer(message, client_broker);
    }
    // client_broker->addMessage(0, 1, message);

    std::cout << "ClientBroker is stopping" << std::endl;

    delete client_broker;
    delete network_module;
    return 0;
}
