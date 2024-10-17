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
    /**
     * @brief Virtual destructor for ISession.
     */
    virtual ~ISession() = default;

    /**
     * @brief Reads data from the session.
     *
     * This pure virtual function must be implemented to handle the logic
     * for reading data from the session.
     *
     * @param onDisconnected A function to be called when the session is disconnected.
     * @param onReceive A function to be called when data is received.
     */
    virtual void read(std::function<void(ISession *)> onDisconnected, std::function<void(const Request &request)> onReceive) = 0;

    /**
     * @brief Sends data over TCP.
     *
     * This pure virtual function must be implemented to handle the logic
     * for sending data over TCP.
     *
     * @param request The data to be sent over TCP.
     */
    virtual void sendTCP(const std::string &request) = 0;

    /**
     * @brief Sends data over UDP.
     *
     * This pure virtual function must be implemented to handle the logic
     * for sending data over UDP.
     *
     * @param request The data to be sent over UDP.
     */
    virtual void sendUDP(const std::string &request) = 0;

    /**
     * @brief Sets the callback function for disconnection events.
     *
     * @param onDisconnected A function to be called when the session is disconnected.
     */
    std::uint8_t getId() const { return _id; }

    /**
     * @brief Sets the client ID.
     *
     * @param id The client ID to be set.
     */
    void setId(std::uint8_t id) { _id = id; }

    /**
     * @brief Gets the client ID.
     *
     * @return The client ID.
     */
    bool isConnected() const { return _isConnected; }

    /**
     * @brief Sets the connection status.
     *
     * @param connected The connection status to be set.
     */
    void setConnected(bool connected) { _isConnected = connected; }

    /**
     * @brief Sends a handshake message.
     *
     * This pure virtual function must be implemented to handle the logic
     * for sending a handshake message.
     */
    virtual void handShake() = 0;

protected:
    /**
     * @brief Client ID.
     */
    std::uint8_t _id;
    
    /**
     * @brief Connection status.
     */
    bool _isConnected;

private:
};
