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

class GameScene : public LE::Scene {
    public:
        GameScene() : LE::Scene()
        {
            _ecs = std::make_shared<Ecs>();
            Entity entity = _ecs->createEntity();
            _ecs->registerComponent<TransformComponent>();
            _ecs->registerComponent<SpriteComponent>();
            Signature signature;
            signature.set(_ecs->getComponentType<TransformComponent>());
            signature.set(_ecs->getComponentType<SpriteComponent>());
            _ecs->registerSystem<Render2DSystem>();
            _ecs->setSignature<Render2DSystem>(signature);

            _ecs->addComponent<TransformComponent>(entity, (TransformComponent){{400, 400, 0}, {0, 0, 180}, {0.5f, 0.5f}});
            auto sprite = createSpriteComponent("assets/images/character.png");
            _ecs->addComponent<SpriteComponent>(entity, *sprite);
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