/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** ConnectionTCP
*/

#include "ConnectionTCP.hpp"

ConnectionTCP::ConnectionTCP(int port) :
    _asioAcceptor(_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    _endpoint = _asioAcceptor.local_endpoint();
    _port = port;
}

ConnectionTCP::~ConnectionTCP()
{
}


void ConnectionTCP::WaitForConnection()
{
    _asioAcceptor.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            if (!ec) {
                std::cout << "Connection established" << std::endl;
                std::shared_ptr<TCPSession> newSession = std::make_shared<TCPSession>(std::move(socket));
                newSession->start();
                newSession->write("Hello from server");
                _sessions.push(newSession);
            }
            WaitForConnection();
        });
}


void ConnectionTCP::run()
{
    _threadContext = std::thread([this]() {
        _io_context.run();
    });
}
