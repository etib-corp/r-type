/**
 * @file SessionManager.hpp
 * @brief Header file for the SessionManager class.
 * 
 * This file contains the declaration of the SessionManager class, which is responsible for managing
 * client sessions in a network module. It provides methods to add, remove, and retrieve client sessions,
 * as well as handling received requests.
 */

#pragma once

#include "ISession.hpp"
#include <vector>
#include <memory>
#include "PackUnpack.hpp"
#include <functional>
#include <mutex>

/**
 * @class SessionManager
 * @brief Manages client sessions in a network module.
 * 
 * The SessionManager class provides methods to add, remove, and retrieve client sessions.
 * It also allows setting a callback function to handle received requests.
 */
class SessionManager
{
public:
    /**
     * @brief Constructs a new SessionManager object.
     */
    SessionManager();

    /**
     * @brief Destroys the SessionManager object.
     */
    virtual ~SessionManager();

    /**
     * @brief Adds a client session.
     * 
     * @param client A shared pointer to the client session to be added.
     */
    virtual void addClient(std::shared_ptr<ISession> client);

    /**
     * @brief Retrieves all client sessions.
     * 
     * @return A reference to a vector of shared pointers to client sessions.
     */
    virtual std::vector<std::shared_ptr<ISession>> &getClients();

    /**
     * @brief Retrieves a client session by its ID.
     * 
     * @param id The ID of the client session to be retrieved.
     * @return A shared pointer to the client session with the specified ID.
     */
    virtual std::shared_ptr<ISession> getClientById(std::uint32_t id);

    /**
     * @brief Removes a client session by its ID.
     * 
     * @param id The ID of the client session to be removed.
     */
    virtual void removeClientById(std::uint32_t id);

    /**
     * @brief Sets the callback function to handle received requests.
     * 
     * @param onReceive A function to be called when a request is received.
     */
    void setOnReceive(std::function<void(const Request &)> onReceive);

    /**
     * @brief Retrieves the callback function for handling received requests.
     * 
     * @return The function to be called when a request is received.
     */
    std::function<void(const Request &)> getOnReceive();

    /**
     * @brief Pops a session from the session stack.
     * 
     * @return A shared pointer to the popped session.
     */
    std::shared_ptr<ISession> popSession(void);

    /**
     * @brief Pushes a session onto the session stack.
     * 
     * @param session A shared pointer to the session to be pushed.
     */
    void pushSession(std::shared_ptr<ISession> session);

protected:
    /**
     * @brief Callback function for received requests.
     */
    std::function<void(const Request &)> _onReceive;

    /**
     * @brief Mutex for thread safety.
     */
    std::mutex _mutex;
    
    /**
     * @brief Vector of client sessions.
     */
    std::vector<std::shared_ptr<ISession>> _sessions;

private:
};
