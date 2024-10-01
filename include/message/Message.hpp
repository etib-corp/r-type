#pragma once

#include <cstdint>
#include <string>
#include <map>

#include "PackUnpack.hpp"

/**
 * @class Message
 * @brief A class representing a message with an ECS ID and a topic name.
 *
 * The Message class provides methods to set and get the ECS ID and topic name.
 * It is used to encapsulate message data within the system.
 *
 * @note The destructor is defaulted.
 */
class Message
{
public:
    /**
     * @brief Constructs a new Message object.
     */
    Message(void);

    /**
     * @brief Destroys the Message object.
     */
    ~Message(void);

    /**
     * @brief Sets the ECS ID for the message.
     *
     * @param ecs_id The ECS ID to be set.
     */
    void setECSId(std::uint32_t ecs_id) { _ecs_id = ecs_id; }

    /**
     * @brief Gets the ECS ID of the message.
     *
     * @return The ECS ID of the message.
     */
    std::uint32_t getECSId(void) const { return _ecs_id; }

    /**
     * @brief Sets the topic name for the message.
     *
     * @param topic_name The topic name to be set.
     */
    void setTopicName(const std::string topic_name) { _topic_name = topic_name; }

    /**
     * @brief Gets the topic name of the message.
     *
     * @return A constant reference to the topic name of the message.
     */
    const std::string &getTopicName(void) const { return _topic_name; }

    /**
     * @brief Sets the action for the message.
     *
     * @param action The action to be set.
     */
    void setAction(std::uint8_t action) { _action = action; }

    /**
     * @brief Gets the action of the message.
     *
     * @return The action of the message.
     */
    std::uint8_t getAction(void) const { return _action; }

    /**
     * @brief Serializes the message.
     *
     * @return A unique pointer to the serialized request.
     */
    std::unique_ptr<Request> serialize(void) const;

    /**
     * @brief Deserializes the message.
     *
     * @param request A unique pointer to the request to be deserialized.
     */
    void deserialize(std::unique_ptr<Request> request);

private:
    std::uint32_t _ecs_id;
    std::string _topic_name;
    std::uint8_t _action;
};
