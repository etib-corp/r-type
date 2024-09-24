/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"
#include "PackUnpack.hpp"

int main(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();

    try {
        LoaderLib lb(pathLib, "");
        std::ostringstream oss;
        Entity entity = {.type = "Avion", .action = "Voler", .life = 3};
        Request request = {0x0, 0x01, 0x05, 0x13, 0x0};
        ::memmove(request.Body, &entity, sizeof(Entity));

        oss << request;

        lb.LoadModule();

        INetworkModule *test = lb.createNetworkModule();
        IServer *server = test->createServer(8080);
        server->run();
        while (1) {
            if (server->_sessions.size() > 0) {
                std::shared_ptr<ISession> session = server->getClientById(1);
                std::cout << "Sending: " << oss.str() << std::endl;
                session->sendTCP(oss.str());
                sleep(5);
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
