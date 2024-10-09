/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** Session
*/

#include "Session.hpp"

Session::Session(boost::asio::ip::tcp::socket socket)
    : _socketTCP(std::move(socket)), _socketUDP(_io_service)
{
    _endpoint = _socketTCP.remote_endpoint();
    _socketUDP.open(boost::asio::ip::udp::v4());
}

Session::~Session()
{
}

void Session::read(std::function<void(ISession *)> onDisconnected, std::function<void(const Request &request)> onReceive)
{
    _socketTCP.async_receive(
        boost::asio::buffer(&_data, sizeof(Header)),
        [this, onDisconnected, onReceive](const boost::system::error_code &error, std::size_t bytes_transferred)
        {
            if (!error)
            {
                char *_bodyStr = new char[_data.header.BodyLength];
                std::cout << "Received: " << _data.header.BodyLength << std::endl;
                ::memset(_bodyStr, 0, _data.header.BodyLength);
                std::istringstream iss;
                this->_socketTCP.receive(boost::asio::buffer(_bodyStr, _data.header.BodyLength));
                iss.str(_bodyStr);
                iss >> _data.body;
                onReceive(_data);
                ::memset(&_data, 0, sizeof(Request));
                delete[] _bodyStr;
                read(onDisconnected, onReceive);
            }
            else
            {
                onDisconnected(this);
            }
        });
}

void Session::sendTCP(const std::string &request)
{
    _socketTCP.send(boost::asio::buffer(request));
}

void Session::sendUDP(const std::string &request)
{
    _socketUDP.send_to(boost::asio::buffer(request), _udp_endpoint);
}
