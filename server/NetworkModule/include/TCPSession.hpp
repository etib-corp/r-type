/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** TCPSession
*/

#ifndef TCPSESSION_HPP_
#define TCPSESSION_HPP_

#include <boost/asio.hpp>
#include <memory>
#include <iostream>

/**
 * @class TCPSession
 * @brief Manages a TCP session using Boost.Asio.
 *
 * The TCPSession class handles the lifecycle of a TCP session, including
 * reading from and writing to the socket.
 */
class TCPSession {
    public:
        /**
         * @brief Constructs a new TCPSession object.
         *
         * This constructor initializes a TCPSession with a given TCP socket.
         *
         * @param socket The TCP socket to be used for the session. The socket is moved into the TCPSession object.
         */
        TCPSession(boost::asio::ip::tcp::socket socket);
        ~TCPSession();

        /**
         * @brief Starts the TCP session by initiating the read operation.
         *
         * This function begins the TCP session by calling the read() method,
         * which is responsible for handling incoming data from the network.
         */
        void start();
        /**
         * @brief Initiates an asynchronous read operation on the TCP socket.
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
        void read();

        /**
         * @brief Asynchronously writes a message to the TCP socket.
         *
         * This function sends the provided message over the TCP socket using
         * Boost.Asio's asynchronous write operation. It logs the message to
         * the standard output upon successful transmission.
         *
         * @param message The message to be sent over the TCP socket.
         */
        void write(const std::string& message);

    protected:
        boost::asio::ip::tcp::socket _socket;
        enum { _max_length = 1024 };
        char _data[_max_length];

    private:
};

#endif /* !TCPSESSION_HPP_ */
