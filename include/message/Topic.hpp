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
     * @param id The ID of the topic.
     */
    Topic(std::uint8_t ecs_id, std::uint8_t id);

    /**
     * @brief Destroys the Topic object.
     */
    ~Topic(void);

    /**
     * @brief Adds a message to the topic's queue.
     *
     * @param message A unique pointer to the message to be added.
     */
    void addMessage(Message *message)
    {
        _messages.push(message);
    }

    /**
     * @brief Retrieves and removes the next message from the topic's queue.
     *
     * @return A unique pointer to the next message, or nullptr if the queue is empty.
     */
    Message *getMessage(void)
    {
        if (_messages.empty())
            return nullptr;
        Message *message = _messages.front();
        _messages.pop();
        return message;
    }

private:
    std::uint8_t _ecs_id;
    std::uint8_t _id;
    std::queue<Message *> _messages;
};
