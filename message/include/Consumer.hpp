/**
 * @file Consumer.hpp
 * @brief Defines the Consumer class for consuming messages from a specific topic.
 * 
 * This file contains the declaration of the Consumer class, which is responsible
 * for consuming messages from a specified topic. The class provides methods to
 * initialize the consumer with a topic name and to consume messages.
 * 
 */

#pragma once

#include <string>
#include <memory>

#include "Broker.hpp"

/**
 * @class Consumer
 * @brief A class responsible for consuming messages from a specified topic.
 *
 * The Consumer class provides functionality to consume messages from a given topic.
 * It manages the topic name and provides a method to consume messages.
 */
class Consumer
{
public:
    /**
     * @brief Constructs a Consumer object with the specified topic name.
     *
     * @param topicName The name of the topic from which messages will be consumed.
     */
    Consumer(std::string topicName);

    /**
     * @brief Destructor for the Consumer class.
     */
    ~Consumer(void);

    /**
     * @brief Consumes a message from the topic.
     *
     * @return A unique pointer to the consumed Message object.
     */
    std::unique_ptr<Message> consumeMessage(void);

private:
    /**
     * @brief The name of the topic from which messages will be consumed.
     */
    std::string _topicName;
};
