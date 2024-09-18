/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Producer.cpp
*/

#include "Producer.hpp"
#include "Broker.hpp"

template <typename BrokerType>
Producer<BrokerType>::Producer(std::string topicName) : _topicName(topicName)
{
}

template <typename BrokerType>
Producer<BrokerType>::~Producer(void)
{
}
