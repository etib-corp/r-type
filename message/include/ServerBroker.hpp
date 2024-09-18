
/**
 * @file ServerBroker.hpp
 * @brief Header file for the ServerBroker class.
 *
 * This file contains the declaration of the ServerBroker class, which inherits from the Broker class,
 * and is responsible for handling server-specific broker operations.
 */

#pragma once

#include "Broker.hpp"
#include <mutex>

/**
 * @class ServerBroker
 * @brief A thread-safe singleton class representing a server-side broker.
 *
 * The ServerBroker class is responsible for handling server-specific broker operations.
 */
class ServerBroker : public Broker
{
private:
    static ServerBroker* _instance;
    static std::mutex _mutex;

    /**
     * @brief Constructs a new ServerBroker object.
     * 
     * The constructor is private to prevent direct construction.
     */
    ServerBroker(void) = default;

    /**
     * @brief Destroys the ServerBroker object.
     */
    ~ServerBroker(void) = default;

public:
    /**
     * @brief Singletons should not be cloneable.
     */
    ServerBroker(ServerBroker &other) = delete;

    /**
     * @brief Singletons should not be assignable.
     */
    void operator=(const ServerBroker &) = delete;

    /**
     * @brief This method controls access to the singleton instance.
     * On the first run, it creates the singleton object and stores it in the static pointer.
     * Subsequent calls return the same instance.
     * 
     * @return A pointer to the singleton instance of ServerBroker.
     */
    static ServerBroker* GetInstance()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_instance == nullptr)
        {
            _instance = new ServerBroker();
        }
        return _instance;
    }
};


