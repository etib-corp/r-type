/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IClient
*/

#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#include <iostream>


class IClient {
    public:
        virtual ~IClient() = default;

        virtual void connectToServer(const std::string &ip, const int &port) = 0;

        virtual void readTCP() = 0;

        virtual void readUDP() = 0;

        virtual void sendTCP(const std::string &message) = 0;

        virtual void sendUDP(const std::string &message) = 0;

        virtual int getId() const { return _id; }

        virtual void setId(int id) { _id = id; }

    protected:
        int _id;
    private:
};

#endif /* !ICLIENT_HPP_ */
