/**
 * @file IClient.hpp
 * @brief Interface for client network module.
 *
 * This file defines the IClient interface, which provides methods for
 * connecting to a server, sending and receiving data over TCP and UDP,
 * and handling connection and data reception events.
 */

#pragma once

#include <iostream>
#include "PackUnpack.hpp"
#include <functional>

/**
 * @class IClient
 * @brief Interface for client network operations.
 *
 * The IClient interface provides methods for connecting to a server,
 * sending and receiving data over TCP and UDP, and handling connection
 * and data reception events.
 */
class IClient
{
public:
    /**
     * @brief Virtual destructor for IClient.
     */

    virtual ~IClient() = default;

    /**
     * @brief Connects to the server.
     *
     * This pure virtual function must be implemented to handle the logic
     * for connecting to a server.
     */
    virtual void connectToServer(void) = 0;

    /**
     * @brief Sets the callback function for data reception.
     *
     * @param onReceive A function to be called when data is received.
     */
    virtual void setOnReceive(std::function<void(const Request &)> onReceive) { _onReceive = onReceive; }

    /**
     * @brief Reads data from the server using TCP.
     *
     * This pure virtual function must be implemented to handle the logic
     * for reading data from the server using TCP.
     */
    virtual void readTCP() = 0;

    /**
     * @brief Reads data from the server using UDP.
     *
     * This pure virtual function must be implemented to handle the logic
     * for reading data from the server using UDP.
     */
    virtual void readUDP() = 0;

    /**
     * @brief Sends data to the server using TCP.
     *
     * @param request The data to be sent to the server.
     */

    virtual void sendTCP(const std::string &request) = 0;

    /**
     * @brief Sends data to the server using UDP.
     *
     * @param request The data to be sent to the server.
     */
    virtual void sendUDP(const std::string &request) = 0;

    /**
     * @brief Sets the callback function for connection events.
     *
     * @param onConnect A function to be called when a connection is established.
     */

    void setOnConnect(std::function<void(IClient *)> onConnect) { _onConnect = onConnect; }

    /**
     * @brief Gets the client ID.
     *
     * @return The client ID.
     */
    virtual std::uint8_t getId() const { return _id; }

    /**
     * @brief Sets the client ID.
     *
     * @param id The client ID to be set.
     */
    virtual void setId(std::uint8_t id) { _id = id; }

    /**
     * @brief Performs a handshake with the server.
     *
     * This pure virtual function must be implemented to handle the logic
     * for performing a handshake with the server.
     */
    virtual void handShake() = 0;

protected:
    /**
     * @brief Client ID.
     */
    std::uint8_t _id;

    /**
     * @brief Callback function for connection events.
     */
    std::function<void(IClient *)> _onConnect;

    /**
     * @brief Callback function for data reception events.
     */
    std::function<void(const Request &)> _onReceive;

    /**
     * @brief Request object for TCP communication.
     */
    Request _requestTCP = {};

    /**
     * @brief Request object for UDP communication.
     */
    Request _requestUDP = {};

private:
};
