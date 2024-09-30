/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** ListenerUDP
*/

#include "ListenerUDP.hpp"
#include "interface/INetworkModule/IServer.hpp"
#include "Session.hpp"

ListenerUDP::ListenerUDP(int port)
    : _udpSocket(_io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    _port = port;
}

ListenerUDP::~ListenerUDP()
{
}

void ListenerUDP::run(std::shared_ptr<SessionManager> sessionManager)
{
    _sessionManager = sessionManager;
    startReceive();
    _threadContext = std::thread([this]() {
        _io_context.run();
    });
}

void ListenerUDP::startReceive()
{
    _udpSocket.async_receive_from(
    boost::asio::buffer(_recvBuffer), _remoteEndpoint,
    [this](const boost::system::error_code &error, std::size_t bytes_transferred) {
        handleReceive(error, bytes_transferred);
    });
}

void ListenerUDP::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    (void)bytes_transferred;
    if (!error) {
        try {
            // int id = std::stoi(_recvBuffer.data());
            // std::cout << "ID: " << id << std::endl;
            std::shared_ptr<ISession> client = _sessionManager->_sessions[0];
            if (client != nullptr) {
                dynamic_cast<Session *>(client.get())->setUdpEndpoint(_remoteEndpoint);
                client->sendUDP("Hello from toto");
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
        std::cout << "Received: " << _recvBuffer.data() << std::endl;
        std::cout << "Address: " << _remoteEndpoint << std::endl;
        startReceive();
    }
}
