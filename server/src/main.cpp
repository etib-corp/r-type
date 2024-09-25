/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"
#include "PackUnpack.hpp"

std::string serializeRequest(Request &request)
{
    std::ostringstream oss;

    oss.write(reinterpret_cast<const char*>(&request.header), sizeof(request.header));
    oss.write(reinterpret_cast<const char*>(&request.body), sizeof(request.body));
    return oss.str();
}

int main(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();

    try {
        LoaderLib lb(pathLib, "");
        std::ostringstream oss;
        Request request;
        Header header = {.MagicNumber = 0x21, .ECS_CLIENT_ID = 0x01, .Action = 0x05, .BodyLength = 0x13};
        Body body;
        Entity entity = {.type = "Avion", .action = "Voler", .life = 3};
        ::memmove(&body, &entity, sizeof(Entity));

        showHeader(header);
        showBody(reinterpret_cast<Entity *>(&body));


        oss << body;

        lb.LoadModule();

        INetworkModule *test = lb.createNetworkModule();
        IServer *server = test->createServer(8080);

        server->run();
        while (1) {
            if (server->_sessions.size() > 0) {
                std::shared_ptr<ISession> session = server->getClientById(1);
                // std::cout << "Sending: " << oss.str() << std::endl;
                // request.header = header;
                // request.body = body;
                ::memset(&request, 0, sizeof(Request));
                ::memmove(&request.header, &header, sizeof(Header));
                ::memmove(&request.body, oss.str().c_str(), sizeof(Body));
                // showHeader(request.header);
                // std::cout << "Sending: " << serializeRequest(request)[0] << std::endl;
                request.header.BodyLength = oss.str().size();
                std::cout << "Sending: " << request.header.BodyLength << std::endl;
                session->sendTCP(serializeRequest(request));
                sleep(5);
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
