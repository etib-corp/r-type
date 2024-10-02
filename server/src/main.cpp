/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"
#include "PackUnpack.hpp"
#include "message/ServerBroker.hpp"



int main(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
    LoaderLib loader_lib(pathLib, "");
    INetworkModule *network_module = nullptr;
    ServerBroker *server_broker = nullptr;

    loader_lib.LoadModule();
    network_module = loader_lib.createNetworkModule();
    server_broker = new ServerBroker(network_module, 0, 8080);

    Message *message = nullptr;
    auto sessions = server_broker->getClientsSessions();

    while (1) {
        sessions = server_broker->getClientsSessions();
        if (sessions.size() <= 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "No clients connected. Waiting..." << std::endl;
            continue;
        }
        for (auto &session : sessions) {
            message = new Message();
            server_broker->addMessage(session->getId(), 1, message);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Message sent to client " << session->getId() << std::endl;
            delete message;
        }
    }

    delete server_broker;
    delete network_module;

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

    //     INetworkModule *network_module = lb.createNetworkModule();

    //     server->run();
    //     while (1) {
    //         if (server->_sessionsManager->_sessions.size() > 0) {
    //             std::shared_ptr<ISession> session = server->_sessionsManager->_sessions[0];
    //             session->sendTCP(compressAndPrepare(header, body));
    //             sleep(5);
    //         }
    //     }
    // }
    // catch(const std::exception& e) {
    //     std::cerr << e.what() << '\n';
    // }
    //     std::unique_ptr<ServerBroker> serverBroker = std::make_unique<ServerBroker>(network_module, "127.0.0.1", 8080);

    //     IServer *server = network_module->createServer(8080);

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
}
