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
    std::memset(_data, 0, _max_length);
}

Session::~Session()
{
}

void Session::read(std::function<void(ISession *)> onDisconnected)
{
    _socketTCP.async_read_some(
        boost::asio::buffer(_data, _max_length),
        [this, onDisconnected](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Received: " << _data;
                std::cout << "Size: " << length << std::endl;
                std::memset(_data, 0, _max_length);
                read(onDisconnected);
            } else {
                if (ec == boost::asio::error::eof) {
                    this->setConnected(false);
                    onDisconnected(this);
                } else {
                    std::cerr << "Error: " << ec.message() << std::endl;
                }
            }
        });
}

void Session::sendTCP(const std::string &message)
{
    boost::asio::async_write(
        _socketTCP, boost::asio::buffer(message),
        [this, message](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Sent: " << message;
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
                std::cout << "Sent: " << message;
                std::cout << "Size: " << length << std::endl;
            }
        });
}
