/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** main.cpp
*/

#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char **argv)
{
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));
    boost::asio::ip::tcp::socket socket(io_context);
    acceptor.accept(socket);
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
