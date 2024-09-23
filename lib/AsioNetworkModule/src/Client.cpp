/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(const std::string &ip, const int &port) : _socketTCP(_ioContext), _socketUDP(_ioContext)
{
    _socketUDP.open(boost::asio::ip::udp::v4());
    std::memset(_dataTCP, 0, 1024);
    std::memset(_dataUDP, 0, 1024);
    _endpointTCPServer = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address::from_string(ip), port);
    _endpointUDPServer = boost::asio::ip::udp::endpoint(
        boost::asio::ip::address::from_string(ip), port);
}

Client::~Client()
{
}

void Client::connectToServer()
{
    _socketTCP.connect(_endpointTCPServer);
    readTCP();
    _thread = std::thread([this]() { _ioContext.run(); });
}

void Client::readTCP()
{
    _socketTCP.async_read_some(
        boost::asio::buffer(_dataTCP, 1024),
        [this](const boost::system::error_code &error, std::size_t bytes_transferred) {
            (void)bytes_transferred;
            if (!error) {
                std::cout << "Received: " << _dataTCP << std::endl;
            } else {
                std::cerr << "Error: " << error.message() << std::endl;
            }
            std::memset(this->_dataTCP, 0, 1024);
            this->readTCP();
        });
}

void Client::readUDP()
{
    _socketUDP.async_receive(
        boost::asio::buffer(_dataUDP, 1024),
        [this](const boost::system::error_code &error, std::size_t bytes_transferred) {
            (void)bytes_transferred;
            if (!error) {
                std::cout << "Received: " << _dataUDP << std::endl;
                readUDP();
            }
        });
}

void Client::sendTCP(const std::string &message)
{
    boost::asio::write(_socketTCP, boost::asio::buffer(message));
}

void Client::sendUDP(const std::string &message)
{
    _socketUDP.send_to(boost::asio::buffer(message), _endpointUDPServer);
}
