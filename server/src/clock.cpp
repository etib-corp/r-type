#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <unistd.h>
#include "PackUnpack.hpp"

// // Fonction pour exécuter une série de callbacks
// void executeCallbacks(const std::vector<std::function<void()>>& callbacks) {
//     for (const auto& callback : callbacks) {
//         callback();  // Exécute chaque callback dans l'ordre
//     }
// }

// // Fonction pour traiter le header
// void processHeader(const Header& header, const std::unordered_map<char, std::vector<std::function<void()>>>& actionCallbacks) {
//     // Vérifie si l'action existe dans le map et exécute les callbacks associés
//     auto it = actionCallbacks.find(header.Action);
//     if (it != actionCallbacks.end()) {
//         executeCallbacks(it->second());  // Exécute les callbacks associés à l'action
//     } else {
//         std::cout << "Action inconnue." << std::endl;
//     }
// }

// int main(void)
// {
//     GameClock clock;

//     Header testHeader1 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'T'};
//     Header testHeader2 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'L'};
//     Header testHeader3 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'R'};
//     Header testHeader4 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'F'};

//     clock.addCallback([]()
//     {
//         std::cout << "Callback A: send data on all client 100 ms" << std::endl;
//     }, 100);

//     clock.addCallback([]()
//     {
//         std::cout << "Callback B: test 1000 ms" << std::endl;
//     }, 1000);

//     std::unordered_map<char, std::vector<std::function<void()>>> actionCallbacks = {
//         {'T', {callbackT1, callbackT2, callbackT3}},
//         {'L', {callbackL1, callbackL2}},
//         {'R', {callbackR}},
//         {'F', {callbackF}}
//     };

//     processHeader(testHeader1, actionCallbacks);
//     processHeader(testHeader2, actionCallbacks);
//     processHeader(testHeader3, actionCallbacks);
//     processHeader(testHeader4, actionCallbacks);
//     return 0;

//     clock.start();

//     // std::this_thread::sleep_for(std::chrono::seconds(50));
//     // std::shared_ptr<Ecs> _ecs = std::make_shared<Ecs>();
//     // Entity entity = _ecs->createEntity();
//     // _ecs->registerComponent<TransformComponent>();
//     // _ecs->registerComponent<SpriteComponent>();
//     // _ecs->registerComponent<ModelComponent>();

//     while (true) {
//         sleep(5);
//         std::cout << "toto" << std::endl;
//     }

//     clock.stop();

//     return 0;
// }

void callbackInputT1(void)
{
    std::cout << "Callback Input T1 executed." << std::endl;
}

void callbackInputT2(void)
{
    std::cout << "Callback Input T2 executed." << std::endl;
}

void callbackInputT3(void)
{
    std::cout << "Callback Input T3 executed." << std::endl;
}

void callbackInputL1(void)
{
    std::cout << "Callback Input L1 executed (Login step 1)." << std::endl;
}

void callbackInputL2(void)
{
    std::cout << "Callback Input L2 executed (Login step 2)." << std::endl;
}

void callbackInputR(void)
{
    std::cout << "Action R triggered (Register)." << std::endl;
}

void callbackInputF(void)
{
    std::cout << "Action F triggered (Fetch)." << std::endl;
}

void checkMagicNumber(void)
{
    std::cout << "Magic number checked." << std::endl;
}

void executeCallbacks(const std::vector<std::function<void()>>& callbacks)
{
    for (const auto& callback : callbacks)
    {
        callback();
    }
}

void processHeader(const Header& header, const std::unordered_map<char, std::vector<std::function<void()>>>& actionCallbacks)
{
    auto it = actionCallbacks.find(header.Action);

    if (it != actionCallbacks.end())
    {
        executeCallbacks(it->second);
    }
    else
    {
        std::cout << "Action inconnue." << std::endl;
    }
}

int __main__(void)
{
    // GameClock clock;

    // std::unordered_map<char, std::vector<std::function<void()>>> actionCallbacks = {
    //     {'T', {checkMagicNumber, callbackInputT1, callbackInputT2, callbackInputT3}},
    //     {'L', {checkMagicNumber, callbackInputL1, callbackInputL2}},
    //     {'R', {checkMagicNumber, callbackInputR}},
    //     {'F', {checkMagicNumber, callbackInputF}}
    // };

    // Header testHeader1 = {.MagicNumber = 0x77, .ECS_CLIENT_ID = 2, .Action = 'T'};
    // Header testHeader2 = {.MagicNumber = 0x77, .ECS_CLIENT_ID = 2, .Action = 'L'};
    // Header testHeader3 = {.MagicNumber = 0x77, .ECS_CLIENT_ID = 2, .Action = 'R'};
    // Header testHeader4 = {.MagicNumber = 0x77, .ECS_CLIENT_ID = 2, .Action = 'F'};

    // clock.addCallback([]()
    // {
    //     std::cout << "Callback A: send data on all client 100 ms" << std::endl;
    // }, 100);

    // clock.addCallback([]()
    // {
    //     std::cout << "Callback B: test 1000 ms" << std::endl;
    // }, 1000);


    // clock.start();

    // while (true) {
    //     sleep(5);
    //     processHeader(testHeader1, actionCallbacks);
    //     processHeader(testHeader2, actionCallbacks);
    //     processHeader(testHeader3, actionCallbacks);
    //     processHeader(testHeader4, actionCallbacks);
    // }

    // clock.stop();

    return 0;
}


// /*
// ** EPITECH PROJECT, 2024
// ** r-type
// ** File description:
// ** main
// */

// #include "LoaderLib.hpp"
// #include "ResolvingLib.hpp"
// #include "PackUnpack.hpp"

// std::string serializeRequest(Request &request)
// {
//     std::ostringstream oss;

//     oss.write(reinterpret_cast<const char*>(&request.header), sizeof(request.header));
//     oss.write(reinterpret_cast<const char*>(&request.body), sizeof(uint8_t) * request.header.BodyLength);
//     return oss.str();
// }

// void coreCompute(void)
// {
//     // Header testHeader1 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'T'};
//     // Header testHeader2 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'L'};
//     // Header testHeader3 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'R'};
//     // Header testHeader4 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'F'};


// }

// std::string compressAndPrepare(Header header, Body body)
// {
//     Request request;
//     std::ostringstream oss;

//     oss << body;
//     // ::memset(&request, 0, sizeof(Request));
//     ::memmove(&request.header, &header, sizeof(Header));
//     ::memmove(&request.body, oss.str().c_str(), sizeof(Body));
//     request.header.BodyLength = oss.str().size();
//     return serializeRequest(request);
// }

// int main(void)
// {
//     std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();

//     try {
//         LoaderLib lb(pathLib, "");
//         std::ostringstream oss;
//         Request request;
//         Header header = {.MagicNumber = 0x21, .ECS_CLIENT_ID = 0x01, .Action = 0x05, .BodyLength = 0x13};
//         Body body;
//         _Entity entity = {.type = "Avion[PADING][PADING][PADING][PADING][PADING][PADING][PADING][PADING][PADING][PADING]", .action = "Voler[PADING][PADING][PADING][PADING][PADING][PADING][PADING]Voler[PADING][PADING][PADING][PADING][PADING][PADING][PADING]Voler[PADING][PADING][PADING][PADING][PADING][PADING][PADING]", .life = 3};
//         ::memmove(&body, &entity, sizeof(_Entity));

//         showHeader(header);
//         showBody(reinterpret_cast<_Entity *>(&body));


//         oss << body;

//         lb.LoadModule();

//         INetworkModule *test = lb.createNetworkModule();
//         IServer *server = test->createServer(8080);

//         server->run();
//         while (1) {
//             if (server->_sessionsManager->_sessions.size() > 0) {
//                 std::shared_ptr<ISession> session = server->_sessionsManager->_sessions[0];
//                 // std::cout << "Sending: " << oss.str() << std::endl;
//                 // request.header = header;
//                 // request.body = body;



//                 // ::memset(&request, 0, sizeof(Request));
//                 // ::memmove(&request.header, &header, sizeof(Header));
//                 // ::memmove(&request.body, oss.str().c_str(), sizeof(Body));
//                 // request.header.BodyLength = oss.str().size();
//                 // session->sendTCP(serializeRequest(request));

//                 session->sendTCP(compressAndPrepare(header, body));
//                 sleep(5);
//                 coreCompute();

//             }
//         }
//     }
//     catch(const std::exception& e) {
//         std::cerr << e.what() << '\n';
//     }
// }
