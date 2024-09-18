/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Consumer.cpp
*/

#include "Consumer.hpp"
#include "Broker.hpp"

Consumer::Consumer(std::string topicName)
    : _topicName(topicName)
{
}

Consumer::~Consumer(void)
{
}

std::unique_ptr<Message> Consumer::consumeMessage(void)
{
    return Broker::getInstance().getTopic(_topicName)->consumeMessage();
}
