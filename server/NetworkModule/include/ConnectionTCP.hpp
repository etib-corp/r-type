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

/**
 * @class ConnectionTCP
 * @brief Manages TCP connections for the server.
 *
 * This class is responsible for handling TCP connections using Boost.Asio.
 * It provides methods to wait for incoming connections and to run the connection handling loop.
 */
class ConnectionTCP {
    public:
        /**
         * @brief Constructs a new ConnectionTCP object.
         *
         * This constructor initializes the TCP connection acceptor with the specified port.
         * It sets up the ASIO acceptor to listen on the given port using the IPv4 protocol.
         *
         * @param port The port number on which the TCP connection will be accepted.
         */
        ConnectionTCP(int port);

        ~ConnectionTCP();

        /**
         * @brief Asynchronously waits for incoming TCP connections.
         *
         * This function initiates an asynchronous accept operation to wait for
         * incoming TCP connections. When a connection is established, it creates
         * a new TCPSession, starts it, sends a welcome message, and stores the
         * session. The function then recursively calls itself to continue waiting
         * for new connections.
         *
         * @note This function uses Boost.Asio for asynchronous operations.
         */
        void WaitForConnection();

        /**
         * @brief Starts the TCP connection by running the I/O context in a separate thread.
         *
         * This function initializes a new thread that runs the I/O context associated with the TCP connection.
         * It ensures that the I/O operations are handled asynchronously.
         */
        void run();

        /**
         * @brief A queue that holds shared pointers to TCPSession objects.
         *
         * This queue is used to manage and store active TCP sessions. Each session
         * is represented by a shared pointer to a TCPSession object, ensuring proper
         * memory management and reference counting.
         */
        std::queue<std::shared_ptr<TCPSession>> _sessions;

    protected:
        /**
         * @brief The io_context object provides core I/O functionality for asynchronous operations.
         *
         * This object is used to initiate and manage asynchronous operations. It is the main
         * entry point for all I/O operations in the Boost.Asio library. The io_context object
         * runs the event loop that processes asynchronous operations.
         */
        boost::asio::io_context _io_context;

        /**
         * @brief An acceptor used to listen for and accept incoming TCP connections.
         *
         * This member utilizes Boost.Asio's TCP acceptor to manage incoming connection requests.
         * It is responsible for accepting new connections on a specific endpoint.
         */
        boost::asio::ip::tcp::acceptor _asioAcceptor;

        /**
         * @brief Represents a TCP endpoint which includes an IP address and a port number.
         *
         * This member variable is used to specify the remote endpoint for a TCP connection.
         * It is part of the Boost.Asio library, which provides a consistent asynchronous
         * model using a modern C++ approach.
         */
        boost::asio::ip::tcp::endpoint _endpoint;

        /**
         * @brief Thread object for managing the context of the connection.
         *
         * This thread is responsible for handling the operations and
         * communication for the TCP connection in a separate execution
         * context to ensure non-blocking behavior and efficient handling
         * of network tasks.
         */
        std::thread _threadContext;
    
        /**
         * @brief The port number used for the TCP connection.
         */
        int _port;
    private:
};

#endif /* !CONNECTIONTCP_HPP_ */
