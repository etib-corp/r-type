/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() : _socketTCP(_ioService), _socketUDP(_ioService)
{
    _socketUDP.open(boost::asio::ip::udp::v4());
}

Client::~Client()
{
}

void Client::connectToServer(const std::string &ip, const int &port)
{
    _endpointTCPServer = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address::from_string(ip), port);
    _endpointUDPServer = boost::asio::ip::udp::endpoint(
        boost::asio::ip::address::from_string(ip), port);
    _socketTCP.connect(_endpointTCPServer);
    _thread = std::thread([this]() { _ioService.run(); });
}

void Client::readTCP()
{
}

void Client::sendTCP(const std::string &message)
{
    boost::asio::write(_socketTCP, boost::asio::buffer(message));
}

void Client::sendUDP(const std::string &message)
{
    _socketUDP.send_to(boost::asio::buffer(message), _endpointUDPServer);
}

extern "C" {
    IClient *createClient()
    {
        return new Client();
    }
}
