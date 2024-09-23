#include <iostream>

#include "message/ServerBroker.hpp"

void ServerBroker::_networkRoutine(void)
{
    std::cout << "ServerBroker networkRoutine" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void ServerBroker::_logicalRoutine(void)
{
    std::cout << "ServerBroker logicalRoutine" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void ServerBroker::_run(void)
{
    while (_is_thread_running)
    {
        _networkRoutine();
        _logicalRoutine();
    }
}

void ServerBroker::addMessage(std::uint32_t ecs_id, const std::string &topic_name, std::unique_ptr<Message> message)
{
}