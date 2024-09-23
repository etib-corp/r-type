/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "ListenerTCP.hpp"
#include "ListenerUDP.hpp"
#include "interface/INetworkModule/IServer.hpp"

class Server : public IServer {
    public:
        Server(int port);
        ~Server();

        void routine(void) override;

    protected:
    private:
};

#endif /* !SERVER_HPP_ */
