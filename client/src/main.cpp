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
#include "ECS/Ecs.hpp"
#include "etibjson.hpp"

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

class GameScene : public LE::Scene {
    public:
        GameScene() : LE::Scene()
        {
            _ecs = std::make_shared<Ecs>();
            _ecs->registerComponent<TransformComponent>();
            _ecs->registerComponent<SpriteComponent>();
            _ecs->registerComponent<ModelComponent>();
            _ecs->registerComponent<PatternComponent>();
            _ecs->registerComponent<MotionComponent>();
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
                std::cout << transform << std::endl;
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
    auto scene = std::make_shared<GameScene>();
    engine->addScene("game", scene);
    engine->run(true);
    return 0;
}

#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"
#include "interface/INetworkModule/INetworkModule.hpp"
#include <cstring>
#include <sstream>
#include "PackUnpack.hpp"
#include "message/ClientBroker.hpp"

bool deserializeRequest(const char* data, std::size_t length, std::istringstream *request)
{
    if (length < sizeof(std::istringstream))
    {
        std::cerr << "Erreur: Données reçues trop courtes." << std::endl;
        return false;
    }

    ::memmove(request, data, sizeof(std::istringstream));
    return true;
}

int _main(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();

    try {
        Request request;
        Header header;
        Body body;
        Entity entity;
        LoaderLib lb(pathLib, "");
        std::istringstream iss;
        lb.LoadModule();

        INetworkModule *module = lb.createNetworkModule();

        IClient *client = module->createClient("127.0.0.1", 8080);

        client->connectToServer();
        // client->sendTCP("Hello 0from client TCP\n");
        client->sendUDP("Hello from client UDP\n");
        while (true) {
            // char *data = client->getDataTCP();
            // if (::strlen(data)) {
            //     ::memmove(&request.header, data, sizeof(Header));
            //     std::cout << sizeof(Header) << std::endl;
            //     // showHeader(request.header);
            //     // deserializeRequest(data + sizeof(Header), 2048, &iss);
            //     // ::memmove(&iss.str(), data + sizeof(Header), 2048);
            //     showHeader(request.header);
            //     char *request_body = data + sizeof(Header);
            //     std::istringstream sub_iss;
            //     sub_iss.str(request_body);
            //     // header = request.header;
            //     // std::cout << header.BodyLength << std::endl;
            //     // static_cast<std::istringstream>(request.body) >> body;
            //     // iss.str(client->getDataTCP());
            //     // iss >> body;
            //     sub_iss >> body;
            //     // showHeader(header);
            //     showBody(reinterpret_cast<Entity *>(&body));
            //     ::memset(client->getDataTCP(), 0, 1024);
            // }
        }

    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    std::unique_ptr<ClientBroker> client_broker = std::make_unique<ClientBroker>("127.0.0.1", 4242);

    return 0;
}
