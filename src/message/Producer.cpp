/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Producer.cpp
*/

#include "message/Producer.hpp"
#include "message/Broker.hpp"

Producer::Producer(std::string topicName)
    : _topicName(topicName)
{
}

Producer::~Producer(void)
{
}

void Producer::produceMessage(std::unique_ptr<Message> message)
{
    Broker::getInstance().getTopic(_topicName).produceMessage(std::move(message));
}
