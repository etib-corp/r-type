#include "message/Broker.hpp"

void Broker::_networkRoutine(void)
{
    _sendMessages();
}
void Broker::_logicalRoutine(void)
{
    Message *message = nullptr;
    while (!_incomming_messages.empty())
    {
        _mutex.lock();
        message = _incomming_messages.front();
        _incomming_messages.pop();
        if (_topics.find(std::make_pair(message->getECSId(), message->getTopicName())) == _topics.end())
            _topics[std::make_pair(message->getECSId(), message->getTopicName())] = std::make_unique<Topic>(message->getECSId(), message->getTopicName(), Topic::Type::RECEIVE);
        _topics[std::make_pair(message->getECSId(), message->getTopicName())]->addMessage(message);
        _mutex.unlock();
    }
}

void Broker::_routine(void)
{
    _networkRoutine();
    _logicalRoutine();
}

void Broker::_run(void)
{
    _is_running = true;
    _mutex.unlock();
    while (_is_running)
        _routine();
    std::cout << "Broker routine stopped" << std::endl;
}

void Broker::_stop(void)
{
    std::cout << "Broker is stopping" << std::endl;
    _mutex.lock();
    _is_running = false;
    _mutex.unlock();
    std::cout << "Broker is joining thread" << std::endl;
    _thread.join();
    std::cout << "Broker thread joined" << std::endl;
}

void Broker::_sendMessages(void)
{
    Message *message = nullptr;
    while (!_outgoing_messages.empty())
    {
        _mutex.lock();
        message = _outgoing_messages.front().first;
        _outgoing_messages.pop();
        _sendFunction(message);
        _mutex.unlock();
    }
}
