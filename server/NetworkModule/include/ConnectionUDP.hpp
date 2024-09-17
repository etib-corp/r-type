/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** ConnectionUDP
*/

#ifndef CONNECTIONUDP_HPP_
#define CONNECTIONUDP_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>

class ConnectionUDP {
    public:
        ConnectionUDP(int port);
        ~ConnectionUDP();

        void run();

        void startReceive();
        void handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred);

    protected:
        void Send(const std::string &message);
        boost::asio::io_context _io_context;
        boost::asio::ip::udp::socket _udpSocket;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        std::array<char, 1024> _recvBuffer;
        std::thread _threadContext;
        int _port;
    private:
};

#endif /* !CONNECTIONUDP_HPP_ */
