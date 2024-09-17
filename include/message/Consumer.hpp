/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Consumer.hpp
*/

#pragma once

#include <string>
#include <memory>

#include "message/Broker.hpp"

class Consumer
{
public:
    Consumer(std::string topicName);
    ~Consumer(void);

    std::unique_ptr<Message> consumeMessage(void);

private:
    std::string _topicName;
};
