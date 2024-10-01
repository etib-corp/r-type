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

std::string serializeRequest(Request &request)
{
    std::ostringstream oss;

    oss.write(reinterpret_cast<const char*>(&request.header), sizeof(request.header));
    oss.write(reinterpret_cast<const char*>(&request.body), sizeof(uint8_t) * request.header.BodyLength);
    return oss.str();
}

void coreCompute(void)
{
    // Header testHeader1 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'T'};
    // Header testHeader2 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'L'};
    // Header testHeader3 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'R'};
    // Header testHeader4 = {.MagicNumber = 0X7777, .ECS_CLIENT_ID = 2, .Action = 'F'};


}

std::string compressAndPrepare(Header header, Body body)
{
    Request request;
    std::ostringstream oss;

    oss << body;
    // ::memset(&request, 0, sizeof(Request));
    ::memmove(&request.header, &header, sizeof(Header));
    ::memmove(&request.body, oss.str().c_str(), sizeof(Body));
    request.header.BodyLength = oss.str().size();
    return serializeRequest(request);
}

int main(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();
    LoaderLib loader_lib(pathLib, "");
    INetworkModule *network_module = nullptr;
    ServerBroker *server_broker = nullptr;

    loader_lib.LoadModule();
    network_module = loader_lib.createNetworkModule();
    server_broker = new ServerBroker(network_module, 1, 8080);
    delete server_broker;
    delete network_module;

    try {
        LoaderLib lb(pathLib, "");
        std::ostringstream oss;
        Request request;
        Header header = {.MagicNumber = 0x21, .ECS_CLIENT_ID = 0x01, .Action = 0x05, .BodyLength = 0x13};
        Body body;
        _Entity entity = {.type = "Avion[PADING][PADING][PADING][PADING][PADING][PADING][PADING][PADING][PADING][PADING]", .action = "Voler[PADING][PADING][PADING][PADING][PADING][PADING][PADING]Voler[PADING][PADING][PADING][PADING][PADING][PADING][PADING]Voler[PADING][PADING][PADING][PADING][PADING][PADING][PADING]", .life = 3};
        ::memmove(&body, &entity, sizeof(_Entity));

        server->run();
        while (false) {
            if (server->_sessionsManager->_sessions.size() > 0) {
                std::shared_ptr<ISession> session = server->_sessionsManager->_sessions[0];
                session->sendTCP(compressAndPrepare(header, body));
                sleep(5);
                coreCompute();

            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
