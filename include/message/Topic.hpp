/**
 * @file Topic.hpp
 * @brief Defines the Topic class for managing message queues.
 * 
 * This file contains the declaration of the Topic class, which is responsible
 * for managing message queues. The class provides methods to produce and consume
 * messages in a thread-safe manner using a queue.
 * 
 */

#pragma once

#include <string>
#include <queue>
#include <memory>
#include <mutex>

#include "message/Message.hpp"

/**
 * @class Topic
 * @brief A class that represents a topic for message passing.
 *
 * The Topic class provides mechanisms to produce and consume messages
 * in a thread-safe manner using a queue.
 */
class Topic
{
public:
    /**
     * @brief Constructs a new Topic object.
     *
     * @param name The name of the topic.
     */
    Topic(std::string name);

    /**
     * @brief Destroys the Topic object.
     */

    ~Topic(void);

    /**
     * @brief Produces a new message and adds it to the queue.
     *
     * @param message A unique pointer to the message to be added.
     */

    void produceMessage(std::unique_ptr<Message> message);
    /**
     * @brief Consumes a message from the queue.
     *
     * @return A unique pointer to the consumed message.
     */
    std::unique_ptr<Message> consumeMessage(void);

private:
    /**
     * @brief The name of the topic.
     */
    std::string _name;

    /**
     * @brief The message queue.
     */
    std::queue<std::unique_ptr<Message>> _messages;

    /**
     * @brief Mutex to ensure thread safety.
     */
    std::mutex _mutex;
};
