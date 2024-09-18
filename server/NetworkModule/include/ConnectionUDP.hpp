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

/**
 * @class ConnectionUDP
 * @brief Manages a UDP connection for network communication.
 *
 * The ConnectionUDP class encapsulates the functionality required to manage
 * a UDP connection, including sending and receiving messages. It utilizes
 * Boost.Asio for asynchronous network operations.
 *
 * @note This class is designed to be used in a server environment where
 *       multiple clients may connect and communicate via UDP.
 *
 * @details
 * The ConnectionUDP class provides methods to start receiving messages,
 * handle received messages, and send messages to a remote endpoint. It
 * operates on a separate thread to ensure non-blocking network operations.
 */
class ConnectionUDP {
    public:
        /**
         * @brief Constructs a new ConnectionUDP object.
         *
         * This constructor initializes a UDP socket bound to the specified port.
         *
         * @param port The port number to bind the UDP socket to.
         */
        ConnectionUDP(int port);
        ~ConnectionUDP();

        /**
         * @brief Starts the UDP connection and runs the IO context in a separate thread.
         *
         * This function initiates the receiving process and then creates a new thread
         * to run the IO context. The thread is joined to ensure that the function waits
         * for the thread to complete before returning.
         */
        void run();

        /**
         * @brief Initiates an asynchronous receive operation on the UDP socket.
         *
         * This function starts an asynchronous receive operation using Boost.Asio's
         * async_receive_from method. When data is received, the provided lambda function
         * is called, which in turn calls the handleReceive method with the error code
         * and the number of bytes transferred.
         */
        void startReceive();

        /**
         * @brief Handles the reception of data over UDP.
         *
         * This function is called when data is received on the UDP connection.
         * It processes the received data, sends a response back to the sender,
         * and initiates the next receive operation.
         *
         * @param error The error code indicating the result of the receive operation.
         * @param bytes_transferred The number of bytes received.
         */
        void handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred);

    protected:

        /**
         * @brief Sends a message to the remote endpoint.
         *
         * This function sends a message to the remote endpoint using the UDP socket.
         * It uses Boost.Asio's async_send_to method to send the message asynchronously.
         *
         * @param message The message to send.
         */
        void Send(const std::string &message);

        /**
         * @brief The io_context object provides core I/O functionality for asynchronous operations.
         *
         * This object is used to initiate and manage asynchronous operations. It is the main
         * entry point for all I/O operations in the Boost.Asio library. The io_context object
         * runs the event loop that processes asynchronous operations.
         */
        boost::asio::io_context _io_context;

        boost::asio::ip::udp::socket _udpSocket;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        std::array<char, 1024> _recvBuffer;
        std::thread _threadContext;
        int _port;
    private:
};

#endif /* !CONNECTIONUDP_HPP_ */
