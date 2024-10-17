/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** ListenerUDP
*/

#include "globalLogger.hpp"
#include "ListenerUDP.hpp"
#include "interface/INetworkModule/IServer.hpp"
#include "Session.hpp"

ListenerUDP::ListenerUDP(int port)
    : _udpSocket(_io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    _port = port;
    _udpSocket.set_option(boost::asio::socket_base::reuse_address(true));
}

ListenerUDP::~ListenerUDP()
{
}

void ListenerUDP::run(std::shared_ptr<SessionManager> sessionManager)
{
    _sessionManager = sessionManager;
    startReceive();
    _threadContext = std::thread([this]()
                                 { _io_context.run(); });
}

void ListenerUDP::startReceive()
{
    _udpSocket.async_receive_from(
        boost::asio::buffer(&_request, sizeof(Request)), _remoteEndpoint,
        [this](const boost::system::error_code &error, std::size_t bytes_transferred) {
            handleReceive(error, bytes_transferred);
            ::memset(&_request, 0, sizeof(Request));
            startReceive();
    });
}

void ListenerUDP::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    (void)bytes_transferred;
    if (!error) {
        try {
            if (_request.header.Action == asChar(ActionCode::NEW_CONNECTION)) {
                std::shared_ptr<ISession> session = this->_sessionManager->getClientById(_request.header.EmmiterdEcsId);
                boost::asio::ip::udp::endpoint udp_endpoint(_remoteEndpoint.address(), _remoteEndpoint.port());
                dynamic_cast<Session *>(session.get())->setUdpEndpoint(udp_endpoint);
                rtypeLog->log("{}", "UDP Connection established");
            } else {
                if (_onReceive)
                    _onReceive(_request);
            }
        }
        catch (const std::exception &e)
        {
            rtypeLog->log<LogType::ERR, &std::cerr>("{}", e.what());
        }
    }
}
