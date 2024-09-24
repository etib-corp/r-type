/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IClient
*/

#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#include <iostream>
#include "PackUnpack.hpp"


class IClient {
    public:
        virtual ~IClient() = default;

        virtual void connectToServer(void) = 0;

        virtual void readTCP() = 0;

        virtual void readUDP() = 0;

        virtual void sendTCP(const std::string &message) = 0;

        virtual void sendUDP(const std::string &message) = 0;

        virtual int getId() const { return _id; }

        virtual void setId(int id) { _id = id; }

        virtual char *getDataTCP() { return _dataTCP; }

        virtual char *getDataUDP() { return _dataUDP; }

    protected:
        int _id;
        char _dataTCP[1024] = {0};
        char _dataUDP[1024] = {0};

        Request _requestTCP = {};
        Request _requestUDP = {};
    private:
};

#endif /* !ICLIENT_HPP_ */
