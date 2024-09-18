/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** TCPSession
*/

#include "TCPSession.hpp"

TCPSession::TCPSession(boost::asio::ip::tcp::socket socket)
    : _socket(std::move(socket))
{
}

TCPSession::~TCPSession()
{
}

void TCPSession::start()
{
    read();
}

void TCPSession::read()
{
    _socket.async_read_some(
        boost::asio::buffer(_data, _max_length),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Received: " << _data;
                std::cout << "Size: " << length << std::endl;
            }
            std::memset(_data, 0, _max_length);
            read();
        });
}

void TCPSession::write(const std::string &message)
{
    _socket.async_write_some(
        boost::asio::buffer(message.c_str(), message.size()),
        [this, message](boost::system::error_code ec, std::size_t length) {
            (void)length;
            if (!ec) {
                std::cout << "Sent: " << message << std::endl;
            }
        });
}


