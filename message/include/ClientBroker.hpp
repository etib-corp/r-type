/**
 * @file ClientBroker.hpp
 * @brief Defines the ClientBroker class which inherits from Broker.
 *
 * This file contains the declaration of the ClientBroker class which is responsible
 * for handling client-specific broker functionalities. The class inherits from the
 * base Broker class.
 */

#pragma once

#include <mutex>

#include "Broker.hpp"
#include "LoaderLib.hpp"

/**
 * @class ClientBroker
 * @brief A thread-safe singleton class representing a client-side broker.
 *
 * The ClientBroker class is responsible for handling client-specific
 * broker functionalities. It inherits from the base Broker class.
 */
class ClientBroker : public Broker
{
private:
    static ClientBroker *_instance;
    static std::mutex _mutex;

    /**
     * @brief Constructs a new ClientBroker object.
     *
     * The constructor is private to prevent direct construction.
     */
    ClientBroker(void);

    /**
     * @brief Destroys the ClientBroker object.
     */
    ~ClientBroker(void);

    /**
     * @brief Pointer to the LoaderLib object.
     */
    std::unique_ptr<LoaderLib> _loader_lib;

    /**
     * @brief Pointer to the INetworkModule object.
     */
    std::unique_ptr<INetworkModule> _network_module;

public:
    /**
     * @brief Singletons should not be cloneable.
     */
    ClientBroker(ClientBroker &other) = delete;

    /**
     * @brief Singletons should not be assignable.
     */
    void operator=(const ClientBroker &) = delete;

    /**
     * @brief This method controls access to the singleton instance.
     * On the first run, it creates the singleton object and stores it in the static pointer.
     * Subsequent calls return the same instance.
     *
     * @return A pointer to the singleton instance of ClientBroker.
     */
    static ClientBroker *GetInstance()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_instance == nullptr)
        {
            _instance = new ClientBroker();
        }
        return _instance;
    }
};
