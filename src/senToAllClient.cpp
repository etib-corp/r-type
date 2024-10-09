/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sentToAllClient
*/

#include "SenToAllClient.hpp"

void sendToAllClient(
    std::uint8_t ecsInput,
    std::deque<std::shared_ptr<ISession>> sessions,
    ServerBroker *server_broker,
    Message *message
)
{
    Body body = {0};
    UpdateEcs updateEcs = {.ecs_id = 0x00, .actionInput = ecsInput};

    sessions = server_broker->getClientsSessions();
    if (sessions.size() <= 0)
    {
        std::cout << "No clients connected. Waiting..." << std::endl;
        return;
    }
    ::memmove(body._buffer, &updateEcs, sizeof(updateEcs));
    for (auto &session : sessions)
    {
        message = new Message();
        message->setMagicNumber(0x77);
        message->setAction(static_cast<std::uint8_t>(ActionCode::UPDATE_ECS));
        message->setEmmiterID(0x0);
        message->setBody(body);
        server_broker->addMessage(session->getId(), 1, message);
        std::cout << "Message sent to client <" << session->getId() << ">" << std::endl;
    }
}
