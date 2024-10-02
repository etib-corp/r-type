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
    void setEmmiterID(std::uint32_t emmiter_id) { _emmiter_id = emmiter_id; }

    /**
     * @brief Gets the ECS ID of the message.
     *
     * @return The ECS ID of the message.
     */
    std::uint32_t getEmmiterID(void) const { return _emmiter_id; }

    /**
     * @brief Sets the receiver ID for the message.
     *
     * @param receiver_id The receiver ID to be set.
     */
    void setReceiverID(std::uint32_t receiver_id) { _receiver_id = receiver_id; }

    /**
     * @brief Gets the receiver ID of the message.
     *
     * @return The receiver ID of the message.
     */
    std::uint32_t getReceiverID(void) const { return _receiver_id; }

    /**
     * @brief Sets the topic id for the message.
     *
     * @param topic_name The topic id to be set.
     */
    void setTopicID(std::uint8_t topic_id) { _topic_id = topic_id; }

    /**
     * @brief Gets the topic id of the message.
     * 
     * @return The topic id of the message.
     */
    std::uint8_t getTopicID(void) const { return _topic_id; }

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
    std::string serialize(void) const;

    /**
     * @brief Deserializes the message.
     *
     * @param request A unique pointer to the request to be deserialized.
     */
    void deserialize(std::string raw_request);

private:
    std::uint32_t _emmiter_id;
    std::uint32_t _receiver_id;
    std::uint8_t _topic_id;
    std::uint8_t _action;
};
