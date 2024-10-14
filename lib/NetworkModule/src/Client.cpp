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

    boost::asio::ip::udp::resolver resolver(_ioContext);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), ip, std::to_string(port + 1));  // Use the UDP port
    _endpointUDPServer = *resolver.resolve(query);


    _onReceive = nullptr;
    _onConnect = nullptr;
}

Client::~Client()
{
}

void Client::connectToServer()
{
    readUDP();
    _socketTCP.connect(_endpointTCPServer);
    handShake();
    if (_onConnect)
        _onConnect(this);
    readTCP();
    _thread = std::thread([this]()
                          { _ioContext.run(); });
}

void Client::handShake(void)
{
    _socketTCP.receive(boost::asio::buffer(&_requestTCP, sizeof(Request)));
    std::cout << "Handshake received" << std::endl;
    std::cout << "MagicNumber: " << (int)_requestTCP.header.MagicNumber << std::endl;
    std::cout << "EmmiterEcsId: " << (int)_requestTCP.header.EmmiterdEcsId << std::endl;
    std::cout << "ReceiverEcsId: " << (int)_requestTCP.header.ReceiverEcsId << std::endl;
    std::cout << "TopicID: " << (int)_requestTCP.header.TopicID << std::endl;
    std::cout << "Action: " << (int)_requestTCP.header.Action << std::endl;
    std::cout << "BodyLength: " << (int)_requestTCP.header.BodyLength << std::endl;
    setId(_requestTCP.header.ReceiverEcsId);
    _requestTCP.header.EmmiterdEcsId = getId();
    _requestTCP.header.ReceiverEcsId = 0;
    _socketUDP.send_to(boost::asio::buffer(&_requestTCP, sizeof(Request)), _endpointUDPServer);
}

void Client::readTCP()
{
    _socketTCP.async_receive(
        boost::asio::buffer(&_requestTCP, sizeof(Header)),
        [this](const boost::system::error_code &error, std::size_t bytes_transferred)
        {
            (void)bytes_transferred;
            if (!error)
            {
                if (_requestTCP.header.BodyLength != 0)
                {
                    char *_bodyStr = new char[_requestTCP.header.BodyLength];
                    ::memset(_bodyStr, 0, _requestTCP.header.BodyLength);
                    _socketTCP.receive(boost::asio::buffer(_bodyStr, _requestTCP.header.BodyLength));
                    std::string bodyString(_bodyStr, _requestTCP.header.BodyLength);
                    std::istringstream iss(bodyString);
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
        _endpointUDPReceiver,
        [this](const boost::system::error_code &error, std::size_t bytes_transferred)
        {
            (void)bytes_transferred;
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
