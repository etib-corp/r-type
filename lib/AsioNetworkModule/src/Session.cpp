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

void Session::read(std::function<void(ISession *)> onDisconnected)
{
    _socketTCP.async_receive(
        boost::asio::buffer(&_data, sizeof(Request)),
        [this, onDisconnected](const boost::system::error_code &error, std::size_t bytes_transferred) {
            if (!error) {
                std::istringstream iss;
                showHeader(_data.header);
                this->_socketTCP.receive(boost::asio::buffer(&iss, _data.header.BodyLength));
                iss >> _data.body;
                showBody(reinterpret_cast<_Entity *>(&_data.body));
                read(onDisconnected);
            } else {
                onDisconnected(this);
            }
        });
}

void Session::sendTCP(const std::string &message)
{
    boost::asio::async_write(
        _socketTCP, boost::asio::buffer(message),
        [this, message](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Sent: " << message << std::endl;
                std::cout << "Size: " << length << std::endl;
            }
        });
}

void Session::sendUDP(const std::string &message)
{
    std::cout << "Send udp endpoint: " << _udp_endpoint << std::endl;
    std::cout << "Send Address socket: " << _socketUDP.local_endpoint() << std::endl;
    _socketUDP.async_send_to(
        boost::asio::buffer(message), _udp_endpoint,
        [this, message](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Sent: " << message << std::endl;
                std::cout << "Size: " << length << std::endl;
            }
        });
}
