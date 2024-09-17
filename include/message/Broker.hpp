/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Broker.hpp
*/

#pragma once

#include <map>
#include <mutex>
#include <memory>

#include "message/Topic.hpp"

class Broker
{
public:
    Broker(const Broker &) = delete;
    Broker &operator=(const Broker &) = delete;

    static Broker &getInstance(void)
    {
        static Broker instance;
        return instance;
    }

    void addTopic(const std::string &name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _topics[name] = Topic(name);
    }

    Topic &getTopic(const std::string &topicName)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _topics[topicName];
    }

    void removeTopic(const std::string &topicName)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _topics.erase(topicName);
    }

private:
    Broker(void);
    ~Broker(void);

    std::mutex _mutex;

    std::map<std::string, Topic> _topics;
};
