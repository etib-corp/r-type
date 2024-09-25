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

/**
 * @class Broker
 * @brief Manages topics and messages in a multi-threaded environment.
 *
 * The Broker class is responsible for managing topics and messages. It provides methods to add, retrieve, and
 * remove topics, as well as to add and retrieve messages. It ensures thread safety using mutex locks.
 */
class Broker
{
public:
    /**
     * @brief Destructor for the Broker class.
     */
    ~Broker(void) = default;

    /**
     * @brief Sets the ECS ID for the broker.
     * @param ecs_id The ECS ID to set.
     */
    void setECSId(std::uint32_t ecs_id) { _ecs_id = ecs_id; }

    /**
     * @brief Gets the ECS ID of the broker.
     * @return The ECS ID.
     */
    std::uint32_t getECSId(void) const { return _ecs_id; }

    /**
     * @brief Adds a topic to the broker.
     * @param ecs_id The ECS ID associated with the topic.
     * @param name The name of the topic.
     */
    void addTopic(std::uint32_t ecs_id, const std::string &name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _topics[std::make_pair(ecs_id, name)] = std::make_unique<Topic>(ecs_id, name);
    }

    /**
     * @brief Retrieves a topic from the broker.
     * @param ecs_id The ECS ID associated with the topic.
     * @param name The name of the topic.
     * @return A unique pointer to the topic.
     * @throws std::runtime_error if the topic is not found.
     */
    std::unique_ptr<Topic> &getTopic(std::uint32_t ecs_id, const std::string &name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_topics.find(std::make_pair(ecs_id, name)) == _topics.end())
            throw std::runtime_error("Topic not found");
        return _topics[std::make_pair(ecs_id, name)];
    }

    /**
     * @brief Removes a topic from the broker.
     * @param ecs_id The ECS ID associated with the topic.
     * @param name The name of the topic.
     */
    void removeTopic(std::uint32_t ecs_id, const std::string &name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _topics.erase(std::make_pair(ecs_id, name));
    }

    /**
     * @brief Adds a message to a topic.
     * @param ecs_id The ECS ID associated with the topic.
     * @param topic_name The name of the topic.
     * @param message A unique pointer to the message.
     */
    void addMessage(std::uint32_t ecs_id, const std::string &topic_name, std::unique_ptr<Message> message)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _incomming_messages.push(std::move(message));
    }

    /**
     * @brief Retrieves a message from a topic.
     * @param ecs_id The ECS ID associated with the topic.
     * @param topic_name The name of the topic.
     * @return A unique pointer to the message.
     */
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
