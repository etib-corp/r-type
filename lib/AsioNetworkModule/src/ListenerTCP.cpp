/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** ListenerTCP
*/

#include "ListenerTCP.hpp"
#include "interface/INetworkModule/IServer.hpp"

static int id = 1;

ListenerTCP::ListenerTCP(int port) :
    _asioAcceptor(_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    _endpoint = _asioAcceptor.local_endpoint();
    _port = port;
}

ListenerTCP::~ListenerTCP()
{
}

void ListenerTCP::WaitForConnection()
{
    _asioAcceptor.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            if (!ec) {
                std::cout << "Connection established" << std::endl;
                std::shared_ptr<Session> newSession = std::make_shared<Session>(std::move(socket));
                newSession->setId(id++);
                _server->addClient(newSession);
                newSession->read([this](ISession *session) {
                    std::cout << "Client disconnected: " << session->getId() << std::endl;
                    this->_server->removeClientById(session->getId());
                });
                Request request = {0x0, 0x01, 0x05, 0x13, 0x0};
                newSession->sendTCP(request);
            }
            WaitForConnection();
        });
}

void ListenerTCP::run(IServer* server)
{
    _server = server;
    this->WaitForConnection();
    _threadContext = std::thread([this]() {
        _io_context.run();
    });
}
