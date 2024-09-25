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
    _socketTCP.async_receive(
        boost::asio::buffer(&_requestTCP, sizeof(Header)),
        [this](const boost::system::error_code &error, std::size_t bytes_transferred) {
            std::cout << bytes_transferred << std::endl;
            // (void)bytes_transferred;
            if (!error) {
                char *_bodyStr = new char[1032];
                ::memset(_bodyStr, 0, 1032);
                std::istringstream iss;
                showHeader(_requestTCP.header);
                _socketTCP.receive(boost::asio::buffer(_bodyStr, 1032));
                iss.str(_bodyStr);
                iss >> _requestTCP.body;
                showBody(reinterpret_cast<Entity *>(&_requestTCP.body));
                delete _bodyStr;
            }
            ::memset(&_requestTCP, 0, sizeof(Request));
            readTCP();
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

void Client::sendTCP(const Request &request)
{
    boost::asio::write(_socketTCP, boost::asio::buffer(&request, sizeof(Request)));
}

void Client::sendUDP(const Request &request)
{
    _socketUDP.send_to(boost::asio::buffer(&request, sizeof(Request)), _endpointUDPServer);
}
