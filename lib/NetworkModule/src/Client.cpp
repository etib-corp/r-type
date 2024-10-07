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
    readUDP();
    _socketTCP.connect(_endpointTCPServer);
    readTCP();
    _thread = std::thread([this]()
                          { _ioContext.run(); });
}

void Client::readTCP()
{
    _socketTCP.async_receive(
        boost::asio::buffer(&_requestTCP, sizeof(Header)),
        [this](const boost::system::error_code &error, std::size_t bytes_transferred __attribute__((unused)))
        {
            if (!error)
            {
                if (_requestTCP.header.BodyLength != 0)
                {
                    char *_bodyStr = new char[_requestTCP.header.BodyLength];
                    ::memset(_bodyStr, 0, _requestTCP.header.BodyLength);
                    std::istringstream iss;
                    _socketTCP.receive(boost::asio::buffer(_bodyStr, _requestTCP.header.BodyLength));
                    iss.str(_bodyStr);
                    iss >> _requestTCP.body;
                    delete[] _bodyStr;
                }
                if (_onReceive)
                    _onReceive(_requestTCP);

            }
            ::memset(&_requestTCP, 0, sizeof(Request));
            readTCP();
        });
}

void Client::readUDP()
{
    _socketUDP.async_receive_from(
        boost::asio::buffer(&_requestUDP, sizeof(Request)),
        _endpointUDPServer,
        [this](const boost::system::error_code &error, std::size_t bytes_transferred __attribute__((unused)))
        {
            if (!error)
            {
                if (_onReceive)
                    _onReceive(_requestUDP);
            }
            ::memset(&_requestUDP, 0, sizeof(Request));
            readUDP();
        });
}

void Client::sendTCP(const std::string &request)
{
    boost::asio::write(_socketTCP, boost::asio::buffer(request));
}

void Client::sendUDP(const std::string &request)
{
    _socketUDP.send_to(boost::asio::buffer(request), _endpointUDPServer);
}
