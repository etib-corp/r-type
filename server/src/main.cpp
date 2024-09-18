/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "LoaderLib.hpp"

int main(void)
{
    try {
        LoaderLib lb("./build/server/NetworkModule/libNetworkModule.so", "");

        lb.LoadModule();

        INetworkModule *test = lb.createNetworkModule(8080);
        test->run();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
