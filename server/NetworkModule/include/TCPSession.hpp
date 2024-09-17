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

class TCPSession {
    public:
        TCPSession(boost::asio::ip::tcp::socket socket);
        ~TCPSession();

        void start();
        void read();
        void write(const std::string& message);

    protected:
        boost::asio::ip::tcp::socket _socket;
        enum { _max_length = 1024 };
        char _data[_max_length];

    private:
};

#endif /* !TCPSESSION_HPP_ */
