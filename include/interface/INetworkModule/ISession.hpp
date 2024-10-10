/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ISession
*/

#pragma once

#include <string>
#include <functional>
#include "PackUnpack.hpp"

/**
 * @class ISession
 * @brief Interface for Session communication.
 *
 * This interface defines the basic operations for a Session, including reading
 * data and sending messages over TCP and UDP protocols.
 */
class ISession
{
public:
    virtual ~ISession() = default;

    virtual void read(std::function<void(ISession *)> onDisconnected, std::function<void(const Request &request)> onReceive) = 0;

    virtual void sendTCP(const std::string &request) = 0;

    virtual void sendUDP(const std::string &request) = 0;

    std::uint8_t getId() const { return _id; }

    void setId(std::uint8_t id) { _id = id; }

    bool isConnected() const { return _isConnected; }

    void setConnected(bool connected) { _isConnected = connected; }

protected:
    std::uint8_t _id;
    bool _isConnected;

private:
};
