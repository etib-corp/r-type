#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <queue>

#include "message/Topic.hpp"

#include "LoaderLib.hpp"

class Broker
{
public:
    ~Broker(void) = default;

    void setECSId(std::uint32_t ecs_id) { _ecs_id = ecs_id; }

    std::uint32_t getECSId(void) const { return _ecs_id; }

    void addTopic(std::uint32_t ecs_id, const std::string &name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _topics[std::make_pair(ecs_id, name)] = std::make_unique<Topic>(ecs_id, name);
    }

    std::unique_ptr<Topic> &getTopic(std::uint32_t ecs_id, const std::string &name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_topics.find(std::make_pair(ecs_id, name)) == _topics.end())
            throw std::runtime_error("Topic not found");
        return _topics[std::make_pair(ecs_id, name)];
    }

    void removeTopic(std::uint32_t ecs_id, const std::string &name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _topics.erase(std::make_pair(ecs_id, name));
    }

    void addMessage(std::uint32_t ecs_id, const std::string &topic_name, std::unique_ptr<Message> message)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _incomming_messages.push(std::move(message));
    }

    std::unique_ptr<Message> getMessage(std::uint32_t ecs_id, const std::string &topic_name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return getTopic(ecs_id, topic_name)->getMessage();
    }

protected:
    std::uint32_t _ecs_id;
    std::unique_ptr<LoaderLib> _loader_lib;
    INetworkModule *_network_module;
    std::map<std::pair<std::uint32_t, std::string>, std::unique_ptr<Topic>> _topics;
    std::thread _thread;
    std::mutex _mutex;
    bool _is_running = true;
    std::queue<std::unique_ptr<Message>> _outcomming_messages;
    std::queue<std::unique_ptr<Message>> _incomming_messages;

    virtual void _networkRoutine(void) = 0;

    void _logicalRoutine(void);

    void _routine(void);

    void _run(void);
};
