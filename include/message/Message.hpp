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
    ~Message(void) = default;

    /**
     * @brief Sets the MagicNumber ID for the message.
     *
     * @param magicNumber The MagicNumber ID to be set.
     */
    void setMagicNumber(uint8_t magicNumber) { _magicNumber = magicNumber; }

    /**
     * @brief Gets the MagicNumber ID of the message.
     *
     * @return The MagicNumber ID of the message.
     */
    [[nodiscard]] uint8_t getMagicNumber(void) { return _magicNumber; }

    /**
     * @brief Sets the ECS ID for the message.
     *
     * @param ecs_id The ECS ID to be set.
     */
    void setEmmiterID(std::uint8_t emmiter_id) { _emmiter_id = emmiter_id; }

    /**
     * @brief Gets the ECS ID of the message.
     *
     * @return The ECS ID of the message.
     */
    [[nodiscard]] std::uint8_t getEmmiterID(void) const { return _emmiter_id; }

    /**
     * @brief Sets the receiver ID for the message.
     *
     * @param receiver_id The receiver ID to be set.
     */
    void setReceiverID(std::uint8_t receiver_id) { _receiver_id = receiver_id; }

    /**
     * @brief Gets the receiver ID of the message.
     *
     * @return The receiver ID of the message.
     */
    [[nodiscard]] std::uint8_t getReceiverID(void) const { return _receiver_id; }

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
    [[nodiscard]] std::uint8_t getTopicID(void) const { return _topic_id; }

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
    [[nodiscard]] std::uint8_t getAction(void) const { return _action; }

    /**
     * @brief Sets the header for the message.
     *
     * @param header The header to be set.
     */
    void setHeader(Header header)
    {
        _magicNumber = header.MagicNumber;
        _emmiter_id = header.EmmiterdEcsId;
        _receiver_id = header.ReceiverEcsId;
        _topic_id = header.TopicID;
        _action = header.Action;
    }

    /**
     * @brief Gets the header of the message.
     *
     * @return The header of the message.
     */
    [[nodiscard]]Header getHeader(void)
    {
        Header header = {
            .MagicNumber = _magicNumber,
            .EmmiterdEcsId = _emmiter_id,
            .ReceiverEcsId = _receiver_id,
            .TopicID = _topic_id,
            .Action = _action,
            .BodyLength = 0
        };
        return header;
    }

    /**
     * @brief Sets the body for the message.
     *
     * @param body The body to be set.
     */
    void setBody(Body body) { _body = body; }

    /**
     * @brief Gets the body of the message.
     *
     * @return The body of the message.
     */
    [[nodiscard]] Body getBody(void) const { return _body; }

    /**
     * @brief Sets the request for the message.
     *
     * @param request The request to be set.
     */
    void setRequest(Request request)
    {
        setHeader(request.header);
        setBody(request.body);
    }

    /**
     * @brief Gets the request of the message.
     *
     * @return The request of the message.
     */
    [[nodiscard]] bool isReliable(void) const { return _is_relialbe; }

    /**
     * @brief Sets the reliability of the message.
     *
     * @param is_reliable The reliability of the message.
     */
    void setReliable(bool is_reliable) { _is_relialbe = is_reliable; }


    /**
     * @brief Gets the request of the message.
     *
     * @return The request of the message.
     */
    [[nodiscard]] Request getRequest(void)
    {
        Request request = {
            .header = getHeader(),
            .body = getBody()
        };
        return request;
    }

    /**
     * @brief Serializes the message.
     *
     * @return A unique pointer to the serialized request.
     */
    [[nodiscard]] std::string serialize(void) const;

    /**
     * @brief Deserializes the message.
     *
     * @param request A unique pointer to the request to be deserialized.
     */
    void deserialize(std::string raw_request);

private:
    std::uint8_t _magicNumber;
    std::uint8_t _emmiter_id;
    std::uint8_t _receiver_id;
    std::uint8_t _topic_id;
    std::uint8_t _action;
    Body _body;
    bool _is_relialbe;
};

/**
 * @brief Overloads the << operator for the Message class.
 *
 * @param stream The output stream.
 * @param message The message to be output.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &stream, const Message &message);