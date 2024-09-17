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
        LoaderLib lb("/home/sleo/Documents/interfaceRtype/networkmodule.so", "");

        lb.LoadModule();

        INetworkModule *test = lb.createNetworkModule();
        test->run();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
