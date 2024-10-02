/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"
#include "PackUnpack.hpp"
#include "ECS/Ecs.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "GameClock.hpp"
#include "message/ServerBroker.hpp"


enum class EcsMovement {
    UP      = 0,
    DOWN    = 1,
    RIGHT   = 2,
    LEFT    = 3
};

enum class Axes3D {
    X       = 0,
    Y       = 1,
    Z       = 2,
};

using CallBackFunc = std::function<void(const Header&, std::shared_ptr<Ecs>)>;

void callbackInputUp(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input UP executed." << std::endl;
    std::cout << "Before" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
    _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position[static_cast<int>(Axes3D::Y)] += 1;
    std::cout << "After" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
}

void callbackInputDown(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input Down executed." << std::endl;
    std::cout << "Before" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
    _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position[static_cast<int>(Axes3D::Y)] -= 1;
    std::cout << "After" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
}

void callbackInputLeft(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input Down executed." << std::endl;
    std::cout << "Before" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
    _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position[static_cast<int>(Axes3D::X)] -= 1;
    std::cout << "After" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
}

void callbackInputRight(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input Right executed." << std::endl;
    std::cout << "Before" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
    _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position[static_cast<int>(Axes3D::X)] += 1;
    std::cout << "After" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
}

void checkMagicNumber(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    if (header.MagicNumber == 0xFF)
    {
        std::cout << "Magic number checked." << std::endl;
        return;
    }
    std::cout << "Magic number not good." << std::endl;
}

void executeCallbacks(
    const std::vector<std::function<void(
        const Header&, std::shared_ptr<Ecs>
    )>>& callbacks,
    const Header& header,
    std::shared_ptr<Ecs> _ecs
)
{
    for (const auto& callback : callbacks)
    {
        std::cout << header.Action << std::endl;
        callback(header, _ecs);
    }
}

void processHeader(const Header& header, std::shared_ptr<Ecs> _ecs, const std::unordered_map<char, std::vector<CallBackFunc>>& actionCallbacks)
{
    auto it = actionCallbacks.find(header.Action);

    if (it != actionCallbacks.end())
    {
        executeCallbacks(it->second, header, _ecs);
    }
    else
    {
        std::cout << "Action inconnue." << std::endl;
    }
}

static void receiveFromClient(Message *message, ServerBroker *server_broker, std::shared_ptr<Ecs> _ecs, std::unordered_map<char, std::vector<CallBackFunc>> actionCallbacks)
{
    try {
        message = server_broker->getMessage(0, 1);
        if (message == nullptr)
            return;
        std::cout << "Message received from client" << std::endl;
        std::cout << "acion=" << (int)message->getAction() << std::endl;
        Header header = {
            .Action = message->getAction(),
            .EmmiterdEcsId = (uint8_t)(message)->getEmmiterID(),
            .BodyLength = 0,
            .MagicNumber = 0x77,
            .ReceiverEcsId = (uint8_t)message->getReceiverID()
        };
        processHeader(header, _ecs, actionCallbacks);
        delete message;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cout << "No message received. Waiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

static void sendToAllClient(std::deque<std::shared_ptr<ISession>> sessions, ServerBroker *server_broker, Message *message)
{
    sessions = server_broker->getClientsSessions();
    if (sessions.size() <= 0)
    {
        std::cout << "No clients connected. Waiting..." << std::endl;
        return;
    }
    for (auto &session : sessions)
    {
        message = new Message();
        server_broker->addMessage(session->getId(), 1, message);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Message sent to client " << session->getId() << std::endl;
        delete message;
    }
}

static void receivedFromAllClient(Message *message, ServerBroker *server_broker, std::shared_ptr<Ecs> _ecs, std::unordered_map<char, std::vector<CallBackFunc>> actionCallbacks)
{
    while (true)
    {
        receiveFromClient(message, server_broker, _ecs, actionCallbacks);
    }
}

int main(void)
{
    GameClock clock;
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
    LoaderLib loader_lib(pathLib, "");
    loader_lib.LoadModule();
    Message *message = nullptr;
    INetworkModule *network_module = loader_lib.createNetworkModule();
    ServerBroker *server_broker = new ServerBroker(network_module, 0, 8080);
    auto sessions = server_broker->getClientsSessions();

    std::unordered_map<char, std::vector<CallBackFunc>> actionCallbacks = {
        {'U', {checkMagicNumber, callbackInputUp, [sessions, server_broker, message](const Header &header, std::__1::shared_ptr<Ecs> _ecs){
            sendToAllClient(sessions, server_broker, message);
        }}},
        {'D', {checkMagicNumber, callbackInputDown, [sessions, server_broker, message](const Header &header, std::__1::shared_ptr<Ecs> _ecs){
            sendToAllClient(sessions, server_broker, message);
        }}},
        {'R', {checkMagicNumber, callbackInputRight, [sessions, server_broker, message](const Header &header, std::__1::shared_ptr<Ecs> _ecs){
            sendToAllClient(sessions, server_broker, message);
        }}},
        {'L', {checkMagicNumber, callbackInputLeft, [sessions, server_broker, message](const Header &header, std::__1::shared_ptr<Ecs> _ecs){
            sendToAllClient(sessions, server_broker, message);
        }}}
    };

    clock.addCallback([sessions, server_broker, message]()
    {
        std::cout << "All 100 ms : " << std::endl;;
        // sendToAllClient(sessions, server_broker, message);
    }, 100);

    clock.start();

    std::shared_ptr<Ecs> _ecs = std::make_shared<Ecs>();
    Entity entity = _ecs->createEntity();
    _ecs->registerComponent<TransformComponent>();

    _ecs->addComponent<TransformComponent>(entity, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}});

    receivedFromAllClient(message, server_broker, _ecs, actionCallbacks);

    delete server_broker;
    delete network_module;

    clock.stop();
    return 0;
}
