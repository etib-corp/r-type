#include "message/Broker.hpp"

void Broker::_logicalRoutine(void)
{
    std::unique_ptr<Message> message;
    while (!_incomming_messages.empty())
    {
        message = std::move(_incomming_messages.front());
        _incomming_messages.pop();
        std::lock_guard<std::mutex> lock(_mutex);
        _topics[std::make_pair(message->getECSId(), message->getTopicName())]->addMessage(std::move(message));
    }
}

void Broker::_routine(void)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _networkRoutine();
    _logicalRoutine();
}

void Broker::_run(void)
{
    while (_is_running)
        _routine();
}
