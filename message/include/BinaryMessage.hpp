/**
 * @file BinaryMessage.hpp
 * @brief Defines the BinaryMessage class which inherits from the Message class.
 *
 * This file contains the declaration of the BinaryMessage class which is derived
 * from the Message class. The BinaryMessage class provides functionality specific
 * to binary messages.
 *
 */

#pragma once

#include "Message.hpp"

/**
 * @class BinaryMessage
 * @brief A class representing a binary message.
 *
 * The BinaryMessage class is derived from the Message class and provides
 * functionality specific to binary messages.
 */
class BinaryMessage : public Message
{
public:
    /**
     * @brief Constructs a new BinaryMessage object.
     */
    BinaryMessage(void);

    /**
     * @brief Destroys the BinaryMessage object.
     */
    ~BinaryMessage(void);
};
