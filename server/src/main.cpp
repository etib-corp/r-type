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




void callbackInputUp(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input UP executed." << std::endl;
    std::cout << "Before" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
    _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position[1] += 1;
    std::cout << "After" << _ecs->getComponent<TransformComponent>(header.EmmiterdEcsId).position << std::endl;
}

void callbackInputT2(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input T2 executed." << std::endl;
}

void callbackInputT3(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input T3 executed." << std::endl;
}

void callbackInputL1(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input L1 executed (Login step 1)." << std::endl;
}

void callbackInputL2(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input L2 executed (Login step 2)." << std::endl;
}

void callbackInputR(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Action R triggered (Register)." << std::endl;
}

void callbackInputF(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Action F triggered (Fetch)." << std::endl;
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

void processHeader(const Header& header, std::shared_ptr<Ecs> _ecs, const std::unordered_map<char, std::vector<std::function<void(const Header& header, std::shared_ptr<Ecs> _ecs)>>>& actionCallbacks)
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

static void receiveFromClient( Message *message, ServerBroker *server_broker)
{
    try {
        message = server_broker->getMessage(0, 1);
        std::cout << "Message received from server" << std::endl;
        delete message;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cout << "No message received. Waiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

static void sendToAllClient(auto sessions, ServerBroker *server_broker, Message *message)
{
    sessions = server_broker->getClientsSessions();
    if (sessions.size() <= 0)
    {
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "No clients connected. Waiting..." << std::endl;
        return;
    }
    for (auto &session : sessions)
    {
        message = new Message();
        server_broker->addMessage(session->getId(), 1, message);
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Message sent to client " << session->getId() << std::endl;
        // delete message;
    }
}

static void receivedFromAllClient(void)
{
    while (true) {}
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

    std::unordered_map<char, std::vector<std::function<void(const Header& header, std::shared_ptr<Ecs> _ecs)>>> actionCallbacks = {
        {'U', {checkMagicNumber, callbackInputUp}},
        {'D', {checkMagicNumber, callbackInputL1, callbackInputL2}},
        {'R', {checkMagicNumber, callbackInputR}},
        {'L', {checkMagicNumber, callbackInputF}}
    };

    Header testHeader1 = {.MagicNumber = 0xFF, .EmmiterdEcsId = 1, .ReceiverEcsId = 0, .Action = 'U', .BodyLength = 0};
    Header testHeader2 = {.MagicNumber = 0xFF, .EmmiterdEcsId = 1, .ReceiverEcsId = 0, .Action = 'D', .BodyLength = 0};
    Header testHeader3 = {.MagicNumber = 0xFF, .EmmiterdEcsId = 1, .ReceiverEcsId = 0, .Action = 'R', .BodyLength = 0};
    Header testHeader4 = {.MagicNumber = 0xFF, .EmmiterdEcsId = 1, .ReceiverEcsId = 0, .Action = 'L', .BodyLength = 0};

    clock.addCallback([sessions, server_broker, message]()
    {
        std::cout << "All 100 ms : ";
        sendToAllClient(sessions, server_broker, message);
    }, 100);

    clock.start();

    std::shared_ptr<Ecs> _ecs = std::make_shared<Ecs>();
    Entity entity = _ecs->createEntity();
    _ecs->registerComponent<TransformComponent>();

    _ecs->addComponent<TransformComponent>(entity, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}});

    receivedFromAllClient();

    delete server_broker;
    delete network_module;


    // while (true) {
    //     sleep(5);
    //     processHeader(testHeader1, _ecs, actionCallbacks);
    //     processHeader(testHeader2, _ecs, actionCallbacks);
    //     processHeader(testHeader3, _ecs, actionCallbacks);
    //     processHeader(testHeader4, _ecs, actionCallbacks);
    // }

    Request req;
    req.header.Action = 'U';
    req.header.EmmiterdEcsId = entity;

    if (req.header.Action == 'U')
    {
        std::cout << "Before" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
        _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position[1] += 1;
        std::cout << "After" << _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId).position << std::endl;
    }
    // _ecs->registerComponent<SpriteComponent>();
    // _ecs->registerComponent<ModelComponent>();

    clock.stop();
    return 0;
}
