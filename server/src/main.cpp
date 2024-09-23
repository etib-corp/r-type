/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main
*/

#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"
#include "message/ServerBroker.hpp"

int main(void)
{
    std::unique_ptr<ServerBroker> server_broker = std::make_unique<ServerBroker>(1, 4242);

    return 0;
}
