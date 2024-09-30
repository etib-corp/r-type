/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Server
*/

#pragma once

#include "interface/INetworkModule/IServer.hpp"
#include "ListenerTCP.hpp"
#include "ListenerUDP.hpp"

class Server : public IServer {
    public:
        Server(int port);
        ~Server();

        void run(void) override;

    protected:
    private:
};
