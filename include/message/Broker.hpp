#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <queue>

#include "message/Topic.hpp"

#include "interface/INetworkModule/INetworkModule.hpp"
#include "interface/INetworkModule/INetworkModule.hpp"

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
     * @brief constructor for the Broker class.
     */
    Broker(void) = default;

    /**
     * @brief Destructor for the Broker class.
     */
    ~Broker(void) = default;

    /**
     * @brief Gets the ECS ID of the broker.
     * @return The ECS ID.
     */
    int getECSId(void) const { return _ecs_id; }

    /**
     * @brief Retrieves a topic from the broker.
     * @param ecs_id The ECS ID associated with the topic.
     * @param name The name of the topic.
     * @return A unique pointer to the topic.
     * @throws std::runtime_error if the topic is not found.
     */
    std::unique_ptr<Topic> &getTopic(std::uint32_t ecs_id, std::uint8_t id)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_topics.find(std::make_pair(ecs_id, id)) == _topics.end())
            throw std::runtime_error("Topic not found");
        return _topics[std::make_pair(ecs_id, id)];
    }

    /**
     * @brief Removes a topic from the broker.
     * @param ecs_id The ECS ID associated with the topic.
     * @param name The name of the topic.
     */
    void removeTopic(std::uint32_t ecs_id, std::uint8_t id)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _topics.erase(std::make_pair(ecs_id, id));
    }

    /**
     * @brief Adds a message to a topic.
     * @param ecs_id The ECS ID associated with the topic.
     * @param topic_name The name of the topic.
     * @param message A unique pointer to the message.
     */
    void addMessage(std::uint32_t ecs_id, std::uint8_t topic_id, Message *message)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        message->setEmmiterID(_ecs_id);
        message->setReceiverID(ecs_id);
        message->setTopicID(topic_id);
        // message->setAction(topic_id);
        _outgoing_messages.push(message);
    }

    /**
     * @brief Retrieves a message from a topic.
     * @param ecs_id The ECS ID associated with the topic.
     * @param topic_name The name of the topic.
     * @return A unique pointer to the message.
     */
    Message *getMessage(std::uint32_t ecs_id, std::uint8_t topic_id)
    {
        return getTopic(ecs_id, topic_id)->getMessage();
    }

protected:
    std::uint32_t _ecs_id;
    INetworkModule *_network_module;
    std::map<std::pair<std::uint32_t, std::uint8_t>, std::unique_ptr<Topic>> _topics;
    std::thread _thread;
    std::mutex _mutex;
    bool _is_running = true;
    std::queue<Message *> _outgoing_messages;
    std::queue<Message *> _incomming_messages;
    std::function<void(Message *)> _sendFunction;

    void _setNetworkModule(INetworkModule *network_module) { _network_module = network_module; }

    void _setECSId(int ecs_id) { _ecs_id = ecs_id; }

    void _setSendFunction(std::function<void(Message *)> sendFunction) { _sendFunction = sendFunction; }

    void _networkRoutine(void);

    void _logicalRoutine(void);

    void _routine(void);

    void _run(void);

    void _stop(void);

    virtual void _sendMessage(Message *message) = 0;

    void _sendMessages(void);
};
