/**
 * @file IListenerTCP.hpp
 * @brief Interface for TCP listener modules.
 *
 * This file defines the IListenerTCP interface, which provides methods for
 * waiting for TCP connections and running the listener with a session manager.
 */

#pragma once

#include <queue>
#include <memory>
#include <cstdint>

#include "SessionManager.hpp"

/**
 * @class IListenerTCP
 * @brief Interface for TCP listener modules.
 *
 * The IListenerTCP interface provides methods for waiting for TCP connections
 * and running the listener with a session manager. It also allows setting a
 * callback function to be called when a client connects.
 */
class IListenerTCP
{
public:
    /**
     * @brief Virtual destructor for IListenerTCP.
     */
    virtual ~IListenerTCP() = default;

    /**
     * @brief Waits for a TCP connection.
     *
     * This pure virtual function must be implemented by derived classes to wait
     * for a TCP connection.
     */
    virtual void WaitForConnection() = 0;

    /**
     * @brief Runs the TCP listener with the given session manager.
     *
     * This pure virtual function must be implemented by derived classes to run
     * the TCP listener with the provided session manager.
     *
     * @param module A shared pointer to the SessionManager module.
     */
    virtual void run(std::shared_ptr<SessionManager> module) = 0;

    /**
     * @brief Sets the callback function to be called when a client connects.
     *
     * @param onClientConnected A function to be called when a client connects.
     */
    void setOnClientConnected(std::function<void(ISession *)> onClientConnected) { _onClientConnected = onClientConnected; }

protected:
    /**
     * @brief Callback function for client connection events.
     */
    std::function<void(ISession *)> _onClientConnected = nullptr;

    /**
     * @brief Session manager for the listener.
     */
    std::shared_ptr<SessionManager> _sessionManager;

    /**
     * @brief Last client ID.
     */
    std::uint8_t _last_id = 0;

private:
};
