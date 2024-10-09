/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Client
*/

#pragma once

#include "interface/INetworkModule/IClient.hpp"
#include <boost/asio.hpp>
#include <thread>

class Client : public IClient {
    public:
        Client(const std::string &ip, const int &port);
        ~Client();

        void connectToServer() override;

        void readTCP() override;

        void readUDP() override;

        void sendTCP(const std::string& request) override;

        void sendUDP(const std::string& request) override;

    protected:

        boost::asio::io_context _ioContext;

        boost::asio::ip::tcp::endpoint _endpointTCPServer;
        boost::asio::ip::udp::endpoint _endpointUDPServer;

        boost::asio::ip::tcp::socket _socketTCP;

        boost::asio::ip::udp::socket _socketUDP;

        std::thread _thread;

    private:
};

