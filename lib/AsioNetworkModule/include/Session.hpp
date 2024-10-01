/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** Session
*/

#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <iostream>
#include "interface/INetworkModule/ISession.hpp"

/**
 * @class Session
 * @brief Manages a  session using Boost.Asio.
 *
 * The Session class handles the lifecycle of a  session, including
 * reading from and writing to the socket.
 */
class Session : public ISession {
    public:
        /**
         * @brief Constructs a new Session object.
         *
         * This constructor initializes a Session with a given  socket.
         *
         * @param socket The  socket to be used for the session. The socket is moved into the Session object.
         */
        Session(boost::asio::ip::tcp::socket socket);
        ~Session();

        /**
         * @brief Initiates an asynchronous read operation on the  socket.
         *
         * This function starts an asynchronous read operation using Boost.Asio's
         * `async_read_some` method. It reads data into the `_data` buffer up to
         * `_max_length` bytes. Upon completion of the read operation, the provided
         * lambda function is called.
         *
         * The lambda function checks for errors and, if none are found, prints the
         * received data and its size to the standard output. It then clears the
         * `_data` buffer and recursively calls `read()` to continue reading data.
         *
         * @note This function is designed to be called repeatedly to handle continuous
         *       data reception.
         */
        void read(std::function<void(ISession *)> onDisconnected, std::function<void(const Request& request)> onReceive) override;

        void sendTCP(const std::string& request) override;

        void sendUDP(const std::string& request) override;

        void setUdpEndpoint(boost::asio::ip::udp::endpoint udp_endpoint) { _udp_endpoint = udp_endpoint; }

    protected:
        boost::asio::io_service _io_service;

        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::socket _socketTCP;

        boost::asio::ip::udp::socket _socketUDP;
        boost::asio::ip::udp::endpoint _udp_endpoint;

        Request _data;

    private:
};

