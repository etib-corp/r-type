/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** ConnectionTCP
*/

#ifndef CONNECTIONTCP_HPP_
    #define CONNECTIONTCP_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include "TCPSession.hpp"
#include <thread>

class ConnectionTCP {
    public:
        ConnectionTCP(int port);
        ~ConnectionTCP();

        void WaitForConnection();
        void run();
        std::queue<std::shared_ptr<TCPSession>> _sessions;

    protected:
        boost::asio::io_context _io_context;
        boost::asio::ip::tcp::acceptor _asioAcceptor;
        boost::asio::ip::tcp::endpoint _endpoint;
        std::thread _threadContext;
        int _port;
    private:
};

#endif /* !CONNECTIONTCP_HPP_ */
