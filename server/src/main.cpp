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



void callbackInputT1(const Header& header, std::shared_ptr<Ecs> _ecs)
{
    std::cout << "Callback Input T1 executed." << std::endl;
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

int main(void)
{
    GameClock clock;
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
    std::unordered_map<char, std::vector<std::function<void(const Header& header, std::shared_ptr<Ecs> _ecs)>>> actionCallbacks = {
        {'U', {checkMagicNumber, callbackInputT1, callbackInputT2, callbackInputT3}},
        {'D', {checkMagicNumber, callbackInputL1, callbackInputL2}},
        {'R', {checkMagicNumber, callbackInputR}},
        {'L', {checkMagicNumber, callbackInputF}}
    };

    Header testHeader1 = {.MagicNumber = 0xFF, .ECS_CLIENT_ID = 1, .Action = 'U', .BodyLength = 0};
    Header testHeader2 = {.MagicNumber = 0xFF, .ECS_CLIENT_ID = 1, .Action = 'D', .BodyLength = 0};
    Header testHeader3 = {.MagicNumber = 0xFF, .ECS_CLIENT_ID = 1, .Action = 'R', .BodyLength = 0};
    Header testHeader4 = {.MagicNumber = 0xFF, .ECS_CLIENT_ID = 1, .Action = 'L', .BodyLength = 0};

    clock.addCallback([]()
    {
        std::cout << "Callback A: send data on all client 100 ms" << std::endl;
    }, 100);

    clock.addCallback([]()
    {
        std::cout << "Callback B: test 1000 ms" << std::endl;
    }, 1000);

    // clock.start();


    // try {
    //     LoaderLib lb(pathLib, "");
    //     std::ostringstream oss;
    //     Request request;
    //     Header header = {.MagicNumber = 0x21, .ECS_CLIENT_ID = 0x01, .Action = 0x05, .BodyLength = 0x13};
    //     Body body;
    //     _Entity entity = {.type = "Avion[PADING][PADING][PADING][PADING][PADING]", .action = "Voler[PADING][PADING][PADING][PADING][PADING][PADING][PADING]", .life = 3};
    //     ::memmove(&body, &entity, sizeof(_Entity));

    //     showHeader(header);
    //     showBody(reinterpret_cast<_Entity *>(&body));


    //     oss << body;

    //     lb.LoadModule();

    //     INetworkModule *test = lb.createNetworkModule();
    //     IServer *server = test->createServer(8080);

    //     server->run();
    //     while (1) {
    //         if (server->_sessionsManager->_sessions.size() > 0) {
    //             std::shared_ptr<ISession> session = server->_sessionsManager->_sessions[0];
    //             // std::cout << "Sending: " << oss.str() << std::endl;
    //             // request.header = header;
    //             // request.body = body;
    //             ::memset(&request, 0, sizeof(Request));
    //             ::memmove(&request.header, &header, sizeof(Header));
    //             ::memmove(&request.body, oss.str().c_str(), sizeof(Body));
    //             // showHeader(request.header);
    //             // std::cout << "Sending: " << serializeRequest(request)[0] << std::endl;
    //             request.header.BodyLength = oss.str().size();
    //             session->sendTCP(serializeRequest(request));
    //             sleep(5);
    //         }
    //     }
    // }
    // catch(const std::exception& e) {
    //     std::cerr << e.what() << '\n';
    // }
    std::shared_ptr<Ecs> _ecs = std::make_shared<Ecs>();
    Entity entity = _ecs->createEntity();
    _ecs->registerComponent<TransformComponent>();

    _ecs->addComponent<TransformComponent>(entity, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}});


    while (true) {
        sleep(5);
        processHeader(testHeader1, _ecs, actionCallbacks);
        processHeader(testHeader2, _ecs, actionCallbacks);
        processHeader(testHeader3, _ecs, actionCallbacks);
        processHeader(testHeader4, _ecs, actionCallbacks);
    }

    Request req;
    req.header.Action = 'U';
    req.header.ECS_CLIENT_ID = entity;

    if (req.header.Action == 'U')
    {
        std::cout << "Before" << _ecs->getComponent<TransformComponent>(req.header.ECS_CLIENT_ID).position << std::endl;
        _ecs->getComponent<TransformComponent>(req.header.ECS_CLIENT_ID).position[1] += 1;
        std::cout << "After" << _ecs->getComponent<TransformComponent>(req.header.ECS_CLIENT_ID).position << std::endl;
    }
    // _ecs->registerComponent<SpriteComponent>();
    // _ecs->registerComponent<ModelComponent>();
    clock.stop();

    return 0;
}
