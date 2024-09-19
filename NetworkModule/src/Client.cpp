/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Client
*/

#include "Client.hpp"

Client::Client()
{
    _socketTCP = boost::asio::ip::tcp::socket(_ioService);
    _socketUDP = boost::asio::ip::udp::socket(_ioService);
    _socketUDP.open(boost::asio::ip::udp::v4());
}

Client::~Client()
{
}

void Client::connectToServer(const std::string &ip, const int &port)
{
    _endpointTCPServer = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address::from_string(ip), port);

    _socketTCP.connect(_endpointTCPServer);



}