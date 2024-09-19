/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Producer.cpp
*/

#include "message/Producer.hpp"
#include "message/Broker.hpp"

template <typename BrokerType>
Producer<BrokerType>::Producer(std::string topicName) : _topicName(topicName)
{
}

template <typename BrokerType>
Producer<BrokerType>::~Producer(void)
{
}
