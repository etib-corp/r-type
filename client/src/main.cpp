/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** main
*/

#include <iostream>
// #include <GL/glut.h>
#include "Engine.hpp"
#include "Scene.hpp"
#include <iostream>
#include "PackUnpack.hpp"
#include "ECS/Ecs.hpp"
#include "EnumClass.hpp"
#include <chrono>

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

class MyScene : public LE::Scene {
    public:
        MyScene()
        {
            _ecs = std::make_shared<Ecs>();
            _ecs->registerComponent<TransformComponent>();
            _ecs->registerComponent<SpriteComponent>();
            // _ecs->registerComponent<ModelComponent>();
            Signature signatureRender2D;
            signatureRender2D.set(_ecs->getComponentType<TransformComponent>());
            signatureRender2D.set(_ecs->getComponentType<SpriteComponent>());
            _ecs->registerSystem<Render2DSystem>();
            _ecs->setSignature<Render2DSystem>(signatureRender2D);

            Signature signatureRender3D;
            signatureRender3D.set(_ecs->getComponentType<TransformComponent>());
            // signatureRender3D.set(_ecs->getComponentType<ModelComponent>());
            // _ecs->registerSystem<Render3DSystem>();
            // _ecs->setSignature<Render3DSystem>(signatureRender3D);

            Entity entity = _ecs->createEntity();
            TransformComponent transform = {{400, 400, 0}, {0, 0, 0}, {0.5f, 0.5f, 0.5f}};
            _ecs->addComponent<TransformComponent>(entity, transform);
            auto sprite = createSpriteComponent("assets/images/character.png");
            _ecs->addComponent<SpriteComponent>(entity, *sprite);

            // Entity entity2 = _ecs->createEntity();
            // auto model = createModelComponent("assets/models/buttercup/buttercup.obj");
            // _ecs->addComponent<ModelComponent>(entity2, *model);
            // _ecs->addComponent<TransformComponent>(entity2, (TransformComponent){{400, 400, 0}, {0, 0, 0}, {0.5f, 0.5f, 0.5f}});

        }
        void play() override
        {
            // std::cout << "Game scene updated." << std::endl;
            _eventManager->pollEvents();
            _ecs->update(0.0f);
        }

        void stop() override
        {
            std::cout << "Game scene ended." << std::endl;
        }
};

int __main__(int ac, char **av)
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
