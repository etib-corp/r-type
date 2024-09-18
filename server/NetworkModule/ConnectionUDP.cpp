/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** ConnectionUDP
*/

#include "ConnectionUDP.hpp"


ConnectionUDP::ConnectionUDP(int port)
    : _udpSocket(_io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    _port = port;
}

ConnectionUDP::~ConnectionUDP()
{
}

void ConnectionUDP::run()
{
    startReceive();
    _threadContext = std::thread([this]() {
        _io_context.run();
    });
    _threadContext.join();
}

void ConnectionUDP::startReceive()
{
    _udpSocket.async_receive_from(
    boost::asio::buffer(_recvBuffer), _remoteEndpoint,
    [this](const boost::system::error_code &error, std::size_t bytes_transferred) {
        handleReceive(error, bytes_transferred);
    });
}

void ConnectionUDP::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    (void)bytes_transferred;
    if (!error) {
        std::cout << "Received: " << _recvBuffer.data() << std::endl;
        Send("Hello from server");
        startReceive();
    }
}

void ConnectionUDP::Send(const std::string &message)
{
    _udpSocket.async_send_to(
        boost::asio::buffer(message), _remoteEndpoint,
        [this, message](const boost::system::error_code &error, std::size_t bytes_transferred) {
            (void)bytes_transferred;
            if (!error) {
                std::cout << "Sent: " << message << std::endl;
            }
        });
}
