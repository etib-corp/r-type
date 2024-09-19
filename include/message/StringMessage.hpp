/**
 * @file StringMessage.hpp
 *
 * @brief Defines the StringMessage class which inherits from the Message class.
 *
 * This file contains the declaration of the StringMessage class which is derived
 * from the Message class. The StringMessage class provides functionality specific
 * to string messages.
 */

#pragma once

#include "message/Message.hpp"

/**
 * @class StringMessage
 * @brief A class representing a message that contains a string.
 *
 * The StringMessage class is derived from the Message class and is used to handle
 * messages that specifically contain string data.
 */
class StringMessage : public Message
{
public:
    /**
     * @brief Constructs a new StringMessage object.
     */
    StringMessage(void);

    /**
     * @brief Destroys the StringMessage object.
     */
    ~StringMessage(void);
};
