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
#include "ECS/Ecs.hpp"

class GameScene : public LE::Scene {
    public:
        GameScene() : LE::Scene()
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
            _ecs->addComponent<TransformComponent>(entity, (TransformComponent){{400, 400, 0}, {0, 0, 0}, {0.5f, 0.5f, 0.5f}});
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
