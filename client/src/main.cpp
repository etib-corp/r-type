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
#include "Sound/Sound.hpp"
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
        LE::Sound::Sound *sound = new LE::Sound::Sound("assets/sounds/Pompilili.mp3", LE::Sound::Sound::FileType::MP3);

        sound->play();
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
            _ecs->registerComponent<ModelComponent>();
            _ecs->registerComponent<PatternComponent>();
            _ecs->registerComponent<MotionComponent>();
            _ecs->registerComponent<CameraComponent>();
            Signature signatureRender2D;
            signatureRender2D.set(_ecs->getComponentType<TransformComponent>());
            signatureRender2D.set(_ecs->getComponentType<SpriteComponent>());
            _ecs->registerSystem<Render2DSystem>();
            _ecs->setSignature<Render2DSystem>(signatureRender2D);

            Signature signatureRender3D;
            signatureRender3D.set(_ecs->getComponentType<TransformComponent>());
            signatureRender3D.set(_ecs->getComponentType<ModelComponent>());
            signatureRender3D.set(_ecs->getComponentType<MotionComponent>());
            _ecs->registerSystem<Render3DSystem>();
            _ecs->setSignature<Render3DSystem>(signatureRender3D);

            Signature signaturePattern;
            signaturePattern.set(_ecs->getComponentType<TransformComponent>());
            signaturePattern.set(_ecs->getComponentType<PatternComponent>());
            signaturePattern.set(_ecs->getComponentType<MotionComponent>());
            std::shared_ptr<PatternSystem> patternSystem = _ecs->registerSystem<PatternSystem>();
            _ecs->setSignature<PatternSystem>(signaturePattern);

            Signature signatureCamera;
            signatureCamera.set(_ecs->getComponentType<TransformComponent>());
            signatureCamera.set(_ecs->getComponentType<CameraComponent>());
            signatureCamera.set(_ecs->getComponentType<MotionComponent>());
            _ecs->registerSystem<CameraSystem>();
            _ecs->setSignature<CameraSystem>(signatureCamera);

            patternSystem->addPattern("line", [](PatternComponent &pattern, TransformComponent &transform, MotionComponent &motion) {
                if (transform.position.x != pattern.end_pos.x) {
                    transform.position.x += pattern.speed * (pattern.end_pos.x - transform.position.x > 0 ? 1 : -1);
                }
                if (transform.position.y != pattern.end_pos.y) {
                    transform.position.y += pattern.speed * (pattern.end_pos.y - transform.position.y > 0 ? 1 : -1);
                }
                if (transform.position.z != pattern.end_pos.z) {
                    transform.position.z += pattern.speed * (pattern.end_pos.z - transform.position.z > 0 ? 1 : -1);
                }
            });

            parseJsonAndCreateEnemy(_ecs, "assets/config/vague_1.json");

            // Entity entity = _ecs->createEntity();
            // _ecs->addComponent<TransformComponent>(entity, (TransformComponent){{400, 400, 0}, {0, 0, 0}, {0.5f, 0.5f, 0.5f}});
            // auto sprite = createSpriteComponent("assets/images/character.png");
            // _ecs->addComponent<SpriteComponent>(entity, *sprite);

            Entity cameraEntity = _ecs->createEntity();\
            _ecs->addComponent<TransformComponent>(cameraEntity, (TransformComponent){{0, 0, 0}, {0, 0, 0}, {1.0f, 1.0f, 1.0f}});
            _ecs->addComponent<CameraComponent>(cameraEntity, (CameraComponent){static_cast<float>(LE::Engine::getInstance()->getWindowWidth()), static_cast<float>(LE::Engine::getInstance()->getWindowHeight()), 0.0f, 1000.0f, 45.0f, static_cast<float>(LE::Engine::getInstance()->getWindowWidth()) / static_cast<float>(LE::Engine::getInstance()->getWindowHeight()), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}});
            _ecs->addComponent<MotionComponent>(cameraEntity, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
            _ecs->setCameraEntity(cameraEntity);

            Entity entity2 = _ecs->createEntity();
            auto model2 = createModelComponent("assets/models/ship/MicroRecon.obj");
            _ecs->addComponent<ModelComponent>(entity2, *model2);
            _ecs->addComponent<TransformComponent>(entity2, (TransformComponent){{0, 0, 0}, {0, 90, 0}, {1.0f, 1.0f, 1.0f}});
            _ecs->addComponent<MotionComponent>(entity2, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

            // Entity entity3 = _ecs->createEntity();
            // auto model3 = createModelComponent("assets/models/buttercup/buttercup.obj");
            // _ecs->addComponent<ModelComponent>(entity3, *model3);
            // _ecs->addComponent<TransformComponent>(entity3, (TransformComponent){{0, 0, 0}, {0, 0, 0}, {10.0f, 10.0f, 10.0f}});

            _eventManager = std::make_shared<LE::EventManager>();
            _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_ESCAPE, LE::JUST_PRESSED}, [this, entity2](LE::Engine *engine, float dt) {
                exit(0);
            });
            _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_UP, LE::PRESSED}, [this, entity2](LE::Engine *engine, float dt) {
                auto& motion = _ecs->getComponent<MotionComponent>(entity2);
                motion.velocity.y += 50.0f * (dt / 10000);
            });

            _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_DOWN, LE::PRESSED}, [this, entity2](LE::Engine *engine, float dt) {
                auto& motion = _ecs->getComponent<MotionComponent>(entity2);
                motion.velocity.y -= 50.0f * (dt / 10000);
            });
            _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_RIGHT, LE::PRESSED}, [this, entity2](LE::Engine *engine, float dt) {
                auto& motion = _ecs->getComponent<MotionComponent>(entity2);
                motion.velocity.x += 50.0f * (dt / 10000);
            });

            _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_LEFT, LE::PRESSED}, [this, entity2](LE::Engine *engine, float dt) {
                auto& motion = _ecs->getComponent<MotionComponent>(entity2);
                motion.velocity.x -= 50.0f * (dt / 10000);
            });

            _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_SPACE, LE::JUST_PRESSED}, [this, entity2](LE::Engine *engine, float dt) {
                Entity entity = _ecs->createEntity();
                auto model = createModelComponent("assets/models/bullet/bullet.obj");
                _ecs->addComponent<ModelComponent>(entity, *model);
                auto spaceshipTransform = _ecs->getComponent<TransformComponent>(entity2);
                auto transform = createTransformComponent({spaceshipTransform.position.x, spaceshipTransform.position.y + 6.155F, spaceshipTransform.position.z}, {0, 90, 0}, {0.2f, 0.2f, 0.5f});
                _ecs->addComponent<TransformComponent>(entity, transform);
                _ecs->addComponent<MotionComponent>(entity, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
                auto pattern = createPatternComponent("line", {transform.position[0] + 100, transform.position[1], 0}, 0.05f, PatternEnd::DESTROY);
                _ecs->addComponent<PatternComponent>(entity, pattern);
            });

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

int main(int ac, char **av)
{
    // Initialize the engine
    auto engine = LE::Engine::getInstance();

    // auto scene = std::make_shared<GameScene>();

    // engine->addScene("main", scene);

    engine->addScene("menu", std::make_shared<Menu>());
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
        std::cout << "ECS ID = " << (int)updateEcs.ecs_id << std::endl;
        std::cout << "Action Input" << (int)updateEcs.actionInput << std::endl;
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

// int main(void)
// {
//     std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
//     LoaderLib loader_lib(pathLib, "");
//     INetworkModule *network_module = nullptr;
//     ClientBroker *client_broker = nullptr;

//     loader_lib.LoadModule();
//     network_module = loader_lib.createNetworkModule();
//     client_broker = new ClientBroker(network_module, "127.0.0.1", 8080);

//     Message *message = nullptr;

//     message = new Message();
//     std::string name = "mannuuuuuuuuuu";

//     sendAuthToServer(client_broker, name);

//     Body bodyTest = {._buffer = "|test|test|test|test|"};
//     message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
//     message->setAction(static_cast<uint8_t>(ActionCode::UP));
//     message->setBody(bodyTest);
//     client_broker->addMessage(0, 1, message);
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
//     message->setAction(static_cast<uint8_t>(ActionCode::DOWN));
//     message->setBody(bodyTest);
//     client_broker->addMessage(0, 1, message);
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
//     message->setAction(static_cast<uint8_t>(ActionCode::LEFT));
//     message->setBody(bodyTest);
//     client_broker->addMessage(0, 1, message);
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     message->setMagicNumber(static_cast<uint8_t>(ActionCode::MAGIC_NUMBER));
//     message->setAction(static_cast<uint8_t>(ActionCode::RIGHT));
//     message->setBody(bodyTest);
//     client_broker->addMessage(0, 1, message);
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     while (true)
//     {
//         receiveFromServer(message, client_broker);
//     }
//     // client_broker->addMessage(0, 1, message);

//     std::cout << "ClientBroker is stopping" << std::endl;

//     delete client_broker;
//     delete network_module;
//     return 0;
// }
