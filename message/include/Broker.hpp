/**
 * @file Broker.hpp
 * @brief Singleton class that manages topics.
 * 
 * This file contains the declaration of the Broker class, which is responsible
 * for managing topics in a thread-safe manner. The class provides methods to add,
 * retrieve, and remove topics. The Broker class cannot be copied or assigned.
 * 
 */

#pragma once

#include <map>
#include <mutex>
#include <memory>
#include <stdexcept>

#include "Topic.hpp"

/**
 * @class Broker
 * 
 * @brief Singleton class that manages topics.
 *
 * The Broker class is responsible for managing topics in a thread-safe manner.
 * It provides methods to add, retrieve, and remove topics.
 * This class cannot be copied or assigned.
 */
class Broker
{
public:
    /**
     * @brief Deleted copy constructor.
     */
    Broker(const Broker &) = delete;

    /**
    * @brief Deleted copy assignment operator.
    */
    Broker &operator=(const Broker &) = delete;

    /**
     * @brief Get the singleton instance of the Broker.
     *
     * @return Broker& Reference to the singleton instance.
     */
    static Broker &getInstance(void)
    {
        static Broker instance;
        return instance;
    }

    /**
     * @brief Add a new topic.
     *
     * @param name The name of the topic to add.
     */
    void addTopic(const std::string &name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _topics[name] = Topic(name);
    }

    /**
     * @brief Get a topic by name.
     *
     * @param topicName The name of the topic to retrieve.
     * @return Topic& Reference to the topic.
     */
    Topic &getTopic(const std::string &topicName)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_topics.find(topicName) == _topics.end())
            throw std::runtime_error("Topic not found");
        return _topics[topicName];
    }

    /**
     * @brief Remove a topic by name.
     *
     * @param topicName The name of the topic to remove.
     */
    void removeTopic(const std::string &topicName)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _topics.erase(topicName);
    }

private:
    /**
     * @brief Private constructor to prevent instantiation.
     */
    Broker(void);

    /**
     * @brief Private destructor.
     */
    ~Broker(void);

    /**
     * @brief Mutex to ensure thread safety.
     */
    std::mutex _mutex;

    /**
     * @brief Map of topics.
     */
    std::map<std::string, Topic> _topics;
};
