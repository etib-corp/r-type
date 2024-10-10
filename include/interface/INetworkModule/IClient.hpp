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
#include <functional>

class IClient
{
public:
    virtual ~IClient() = default;

    virtual void connectToServer(void) = 0;

    virtual void setOnReceive(std::function<void(const Request &)> onReceive) { _onReceive = onReceive; }

    virtual void readTCP() = 0;

    virtual void readUDP() = 0;

    virtual void sendTCP(const std::string &request) = 0;

    virtual void sendUDP(const std::string &request) = 0;

    void setOnConnect(std::function<void(IClient *)> onConnect) { _onConnect = onConnect; }

    virtual std::uint8_t getId() const { return _id; }

    virtual void setId(std::uint8_t id) { _id = id; }

protected:
    std::uint8_t _id;

    std::function<void(IClient *)> _onConnect;

    std::function<void(const Request &)> _onReceive;

    Request _requestTCP = {};
    Request _requestUDP = {};

private:
};

#endif /* !ICLIENT_HPP_ */
