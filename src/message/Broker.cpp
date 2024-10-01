#include "message/Broker.hpp"

void Broker::_networkRoutine(void)
{
    _sendMessages();
}

void Broker::_logicalRoutine()
{
    while (!_incomming_messages.empty())
    {
        _mutex.lock();
        auto message = _incomming_messages.front();

        _incomming_messages.pop();
        auto key = std::make_pair(message->getEmmiterID(), message->getTopicID());
        if (_topics.find(key) == _topics.end())
        {
            _topics[key] = std::make_unique<Topic>(message->getEmmiterID(), message->getTopicID());
        }
        _topics[key]->addMessage(message);
        std::cout << "Message received from " << message->getEmmiterID() << " on topic " << message->getTopicID() << std::endl;
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
        message = _outgoing_messages.front();
        _outgoing_messages.pop();
        _sendFunction(message);
        std::cout << "Message sent to " << message->getReceiverID() << std::endl;
        _mutex.unlock();
    }
}
