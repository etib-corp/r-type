/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** ListenerTCP
*/

#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include "Session.hpp"
#include "interface/INetworkModule/IListenerTCP.hpp"
#include <thread>
#include "PackUnpack.hpp"
#include "dllDefine.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

    /**
     * @class ListenerTCP
     * @brief Manages TCP Listeners for the server.
     *
     * This class is responsible for handling TCP Listeners using Boost.Asio.
     * It provides methods to wait for incoming Listeners and to run the Listener handling loop.
     */
    class LIBRARY_API ListenerTCP : public IListenerTCP {
        public:
            /**
             * @brief Constructs a new ListenerTCP object.
             *
             * This constructor initializes the TCP Listener acceptor with the specified port.
             * It sets up the ASIO acceptor to listen on the given port using the IPv4 protocol.
             *
             * @param port The port number on which the TCP Listener will be accepted.
             */
            ListenerTCP(int port);

            ~ListenerTCP();

            /**
             * @brief Asynchronously waits for incoming TCP Listeners.
             *
             * This function initiates an asynchronous accept operation to wait for
             * incoming TCP Listeners. When a Listener is established, it creates
             * a new TCPSession, starts it, sends a welcome message, and stores the
             * session. The function then recursively calls itself to continue waiting
             * for new Listeners.
             *
             * @note This function uses Boost.Asio for asynchronous operations.
             */
            void WaitForConnection() override;

            /**
             * @brief Runs the TCP Listener.
             *
             * This function starts the TCP Listener and runs the Listener handling loop.
             * It sets up the Listener to wait for incoming Listeners and starts the
             * ASIO context to handle the Listener operations.
             */
            void run(std::shared_ptr<SessionManager> sessionManager) override;

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
             * @brief An acceptor used to listen for and accept incoming TCP Listeners.
             *
             * This member utilizes Boost.Asio's TCP acceptor to manage incoming Listener requests.
             * It is responsible for accepting new Listeners on a specific endpoint.
             */
            boost::asio::ip::tcp::acceptor _asioAcceptor;

            /**
             * @brief Represents a TCP endpoint which includes an IP address and a port number.
             *
             * This member variable is used to specify the remote endpoint for a TCP Listener.
             * It is part of the Boost.Asio library, which provides a consistent asynchronous
             * model using a modern C++ approach.
             */
            boost::asio::ip::tcp::endpoint _endpoint;

            /**
             * @brief Thread object for managing the context of the Listener.
             *
             * This thread is responsible for handling the operations and
             * communication for the TCP Listener in a separate execution
             * context to ensure non-blocking behavior and efficient handling
             * of network tasks.
             */
            std::thread _threadContext;

            /**
             * @brief The port number used for the TCP Listener.
             */
            int _port;
        private:
    };

#else

    /**
     * @class ListenerTCP
     * @brief Manages TCP Listeners for the server.
     *
     * This class is responsible for handling TCP Listeners using Boost.Asio.
     * It provides methods to wait for incoming Listeners and to run the Listener handling loop.
     */
    class ListenerTCP : public IListenerTCP {
        public:
            /**
             * @brief Constructs a new ListenerTCP object.
             *
             * This constructor initializes the TCP Listener acceptor with the specified port.
             * It sets up the ASIO acceptor to listen on the given port using the IPv4 protocol.
             *
             * @param port The port number on which the TCP Listener will be accepted.
             */
            ListenerTCP(int port);

            ~ListenerTCP();

            /**
             * @brief Asynchronously waits for incoming TCP Listeners.
             *
             * This function initiates an asynchronous accept operation to wait for
             * incoming TCP Listeners. When a Listener is established, it creates
             * a new TCPSession, starts it, sends a welcome message, and stores the
             * session. The function then recursively calls itself to continue waiting
             * for new Listeners.
             *
             * @note This function uses Boost.Asio for asynchronous operations.
             */
            void WaitForConnection() override;

            /**
             * @brief Runs the TCP Listener.
             *
             * This function starts the TCP Listener and runs the Listener handling loop.
             * It sets up the Listener to wait for incoming Listeners and starts the
             * ASIO context to handle the Listener operations.
             */
            void run(std::shared_ptr<SessionManager> sessionManager) override;

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
             * @brief An acceptor used to listen for and accept incoming TCP Listeners.
             *
             * This member utilizes Boost.Asio's TCP acceptor to manage incoming Listener requests.
             * It is responsible for accepting new Listeners on a specific endpoint.
             */
            boost::asio::ip::tcp::acceptor _asioAcceptor;

            /**
             * @brief Represents a TCP endpoint which includes an IP address and a port number.
             *
             * This member variable is used to specify the remote endpoint for a TCP Listener.
             * It is part of the Boost.Asio library, which provides a consistent asynchronous
             * model using a modern C++ approach.
             */
            boost::asio::ip::tcp::endpoint _endpoint;

            /**
             * @brief Thread object for managing the context of the Listener.
             *
             * This thread is responsible for handling the operations and
             * communication for the TCP Listener in a separate execution
             * context to ensure non-blocking behavior and efficient handling
             * of network tasks.
             */
            std::thread _threadContext;

            /**
             * @brief The port number used for the TCP Listener.
             */
            int _port;
        private:
    };

#endif
