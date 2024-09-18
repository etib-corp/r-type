/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Producer.hpp
*/

#pragma once

#include <string>

#include "message/Message.hpp"

class Producer
{
public:
    Producer(std::string topicName);
    ~Producer(void);

    void produceMessage(std::unique_ptr<Message> message);

private:
    std::string _topicName;
};
