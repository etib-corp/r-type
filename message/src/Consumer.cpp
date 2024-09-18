/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Consumer.cpp
*/

#include "Consumer.hpp"
#include "Broker.hpp"

template <typename BrokerType>
Consumer<BrokerType>::Consumer(std::string topicName) : _topicName(topicName)
{
}

template <typename BrokerType>
Consumer<BrokerType>::~Consumer(void)
{
}
