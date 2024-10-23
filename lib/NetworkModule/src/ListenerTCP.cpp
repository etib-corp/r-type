/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** ListenerTCP
*/

#include "globalLogger.hpp"
#include "ListenerTCP.hpp"
#include "interface/INetworkModule/IServer.hpp"


ListenerTCP::ListenerTCP(int port) : _asioAcceptor(_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    _endpoint = _asioAcceptor.local_endpoint();
    _port = port;
    _last_id = 1;
}

ListenerTCP::~ListenerTCP()
{
}

void ListenerTCP::WaitForConnection()
{
    _asioAcceptor.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                rtypeLog->log("Connection established");
                std::shared_ptr<Session> newSession = std::make_shared<Session>(std::move(socket));
                newSession->setId(_last_id++);
                _sessionManager->addClient(newSession);
                newSession->handShake();
                newSession->read([this](ISession *session)
                                 {
                    rtypeLog->log<LogType::WARN>("Client disconnected: {}", session->getId());
                    this->_sessionManager->removeClientById(session->getId()); }, _sessionManager->getOnReceive());
                if (_onClientConnected) {
                    _onClientConnected(newSession.get());
                }

            }
            WaitForConnection();
        });
}

void ListenerTCP::run(std::shared_ptr<SessionManager> sessionManager)
{
    _sessionManager = sessionManager;
    this->WaitForConnection();
    _threadContext = std::thread([this]()
                                 { _io_context.run(); });
}
