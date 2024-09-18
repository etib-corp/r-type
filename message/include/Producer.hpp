/**
 * @file Producer.hpp
 * @brief Defines the Producer class for producing messages to a specific topic.
 *
 * This file contains the declaration of the Producer class, which is responsible
 * for producing messages to a specified topic. The class provides methods to
 * initialize the producer with a topic name and to produce messages.
 *
 */

#pragma once

#include <string>

#include "Message.hpp"

/**
 * @class Producer
 * @brief A class to produce messages to a specific topic.
 *
 * The Producer class allows for the creation of a producer that can send messages
 * to a specified topic. It manages the topic name and provides a method to produce
 * messages.
 */
class Producer
{
public:
    /**
     * @brief Constructs a new Producer object with a specified topic name.
     *
     * @param topicName The name of the topic to which messages will be produced.
     */
    Producer(std::string topicName);

    /**
     * @brief Destroys the Producer object.
     */
    ~Producer(void);

    /**
     * @brief Produces a message to the topic.
     *
     * @param message A unique pointer to the Message object to be produced.
     */
    void produceMessage(std::unique_ptr<Message> message);

private:
    /**
     * @brief The name of the topic to which messages will be produced.
     */
    std::string _topicName;
};
