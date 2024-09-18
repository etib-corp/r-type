/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Topic.hpp
*/

#pragma once

#include <string>
#include <queue>
#include <memory>
#include <mutex>

#include "message/Message.hpp"

class Topic
{
public:
    Topic(std::string name);
    ~Topic(void);

    void produceMessage(std::unique_ptr<Message> message);
    std::unique_ptr<Message> consumeMessage(void);

private:
    std::string _name;
    std::queue<std::unique_ptr<Message>> _messages;
    std::mutex _mutex;
};
