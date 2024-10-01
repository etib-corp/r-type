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

// std::string serializeRequest(Request &request)
// {
//     std::ostringstream oss;

//     oss.write(reinterpret_cast<const char*>(&request.header), sizeof(request.header));
//     oss.write(reinterpret_cast<const char*>(&request.body), sizeof(uint8_t) * request.header.BodyLength);
//     return oss.str();
// }

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

    try {
        LoaderLib lb(pathLib, "");
        std::ostringstream oss;

        Request request;

    //     lb.LoadModule();

    //     INetworkModule *network_module = lb.createNetworkModule();

        server->_sessionsManager->setOnReceive([&request](const Request &req) {
            ::memmove(&request, &req, sizeof(Request));
            showHeader(request.header);
            std::cout << request.body._buffer << std::endl;
        });


        Request req;
        Header header = {.MagicNumber = 0x21, .ECS_CLIENT_ID = 0x01, .Action = 0x05, .BodyLength = 0x13};
        Body body;
        std::string str = "Hello";
        ::memmove(&body._buffer, str.c_str(), str.size());
        oss << body;

        ::memset(&req, 0, sizeof(Request));
        ::memmove(&req.header, &header, sizeof(Header));
        ::memmove(&req.body, oss.str().c_str(), sizeof(Body));
        req.header.BodyLength = oss.str().size();

        server->run();
        while (1) {
            if (server->_sessionsManager->_sessions.size() > 0) {
                std::shared_ptr<ISession> session = server->_sessionsManager->_sessions[0];
            // //     // std::cout << "Sending: " << oss.str() << std::endl;
            // //     // request.header = header;
            // //     // request.body = body;
            //     ::memset(&request, 0, sizeof(Request));
            //     ::memmove(&request.header, &header, sizeof(Header));
            //     ::memmove(&request.body, oss.str().c_str(), sizeof(Body));
            // //     // showHeader(request.header);
            // //     // std::cout << "Sending: " << serializeRequest(request)[0] << std::endl;
            // //     request.header.BodyLength = oss.str().size();
            session->sendTCP(serializeRequest(req));
                sleep(5);
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
