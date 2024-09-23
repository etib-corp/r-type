/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"

int main(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();

    try {
        LoaderLib lb(pathLib, "");

        lb.LoadModule();

        INetworkModule *test = lb.createNetworkModule();
        IServer *server = test->createServer(8080);
        server->run();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
