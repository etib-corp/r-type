#pragma once

#include <cstdint>
#include <string>
#include <queue>
#include <memory>

#include "message/Message.hpp"

/**
 * @class Topic
 * @brief A class that represents a topic which holds a queue of messages.
 *
 * The Topic class is responsible for managing a queue of messages. It allows
 * adding messages to the queue and retrieving messages from the queue.
 */
class Topic
{
public:
    /**
     * @brief Constructs a new Topic object.
     *
     * @param ecs_id The ID associated with the topic.
     * @param name The name of the topic.
     */

    Topic(std::uint32_t ecs_id, const std::string name);

    /**
     * @brief Destroys the Topic object.
     */
    ~Topic(void);

    /**
     * @brief Adds a message to the topic's queue.
     *
     * @param message A unique pointer to the message to be added.
     */
    void addMessage(std::unique_ptr<Message> message)
    {
        _messages.push(std::move(message));
    }

    /**
     * @brief Retrieves and removes the next message from the topic's queue.
     *
     * @return A unique pointer to the next message, or nullptr if the queue is empty.
     */
    std::unique_ptr<Message> getMessage(void)
    {
        if (_messages.empty())
            return nullptr;
        auto message = std::move(_messages.front());
        _messages.pop();
        return message;
    }

private:
    std::uint32_t _ecs_id;
    std::string _name;
    std::queue<std::unique_ptr<Message>> _messages;
};
