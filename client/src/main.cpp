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

int _main(int ac, char **av)
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

    while (1)
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

    std::cout << "ClientBroker is stopping" << std::endl;

    delete client_broker;
    delete network_module;

    // try
    // {
    //     Request request;
    //     Header header;
    //     Body body;
    //     Entity entity;
    //     LoaderLib lb(pathLib, "");
    //     std::istringstream iss;
    //     lb.LoadModule();

    //     INetworkModule *network_module = lb.createNetworkModule();

    //     IClient *client = network_module->createClient(

    //     client->connectToServer();
    //     client->sendTCP("Hello 0from client TCP\n");
    //     client->sendUDP("Hello from client UDP\n");
    //     while (true) {
    //         char *data = client->getDataTCP();
    //         if (::strlen(data))
    //         {
    //             ::memmove(&request.header, data, sizeof(Header));
    //             std::cout << sizeof(Header) << std::endl;
    //             showHeader(request.header);
    //             deserializeRequest(data + sizeof(Header), 2048, &iss);
    //             ::memmove(&iss.str(), data + sizeof(Header), 2048);
    //             showHeader(request.header);
    //             char *request_body = data + sizeof(Header);
    //             std::istringstream sub_iss;
    //             sub_iss.str(request_body);
    //             header = request.header;
    //             std::cout << header.BodyLength << std::endl;
    //             static_cast<std::istringstream>(request.body) >> body;
    //             iss.str(client->getDataTCP());
    //             iss >> body;
    //             sub_iss >> body;
    //             showHeader(header);
    //             showBody(reinterpret_cast<Entity *>(&body));
    //             ::memset(client->getDataTCP(), 0, 1024);
    //         }
    //     }
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    return 0;
}
