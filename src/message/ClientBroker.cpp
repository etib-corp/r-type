#include <iostream>

#include "message/ClientBroker.hpp"

void ClientBroker::_networkRoutine(void)
{
    std::cout << "ClientBroker networkRoutine" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void ClientBroker::_logicalRoutine(void)
{
    std::cout << "ClientBroker logicalRoutine" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void ClientBroker::_run(void)
{
    while (_is_thread_running)
    {
        _networkRoutine();
        _logicalRoutine();
    }
}

void ClientBroker::addMessage(std::uint32_t ecs_id, const std::string &topic_name, std::unique_ptr<Message> message)
{
}