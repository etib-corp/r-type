/**
 * @file IListenerUDP.hpp
 * @brief Interface for UDP listener module.
 *
 * This file contains the definition of the IListenerUDP interface, which
 * provides methods for running a UDP listener, starting to receive data,
 * and setting a callback function for when data is received.
 */

#pragma once

#include <memory>

#include "SessionManager.hpp"

/**
 * @class IListenerUDP
 * @brief Interface for a UDP listener.
 *
 * The IListenerUDP interface defines methods for running a UDP listener,
 * starting to receive data, and setting a callback function for when data
 * is received. It also holds a port number, a session manager, and a
 * callback function.
 */

class IListenerUDP
{
public:
    /**
     * @brief Destructor for the IListenerUDP interface.
     */

    virtual ~IListenerUDP() = default;

    /**
     * @brief Runs the UDP listener.
     *
     * @param sessionManager A shared pointer to the SessionManager.
     */

    void virtual run(std::shared_ptr<SessionManager> sessionManager) = 0;

    /**
     * @brief Starts receiving data.
     */

    void virtual startReceive() = 0;

    /**
     * @brief Sets the callback function to be called when data is received.
     *
     * @param onReceive A function to be called when data is received.
     */
    void setOnReceive(std::function<void(const Request &)> onReceive) { _onReceive = onReceive; }

protected:
    /**
     * @brief Port number for the listener.
     */
    int _port;

    /**
     * @brief Session manager for the listener.
     */
    std::shared_ptr<SessionManager> _sessionManager;

    /**
     * @brief Callback function for data reception events.
     */
    std::function<void(const Request &)> _onReceive = nullptr;

private:
};
