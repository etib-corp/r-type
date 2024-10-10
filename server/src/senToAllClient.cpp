/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sentToAllClient
*/

#include "SenToAllClient.hpp"

void sendToAllClient(
    std::uint8_t ecsInput,
    ServerBroker *server_broker)
{
    Body body = {0};
    UpdateEcs updateEcs = {.ecs_id = 0x00, .actionInput = ecsInput};
    auto sessions = server_broker->getClientsSessions();

    if (sessions.size() <= 0)
    {
        std::cout << "No clients connected. Waiting..." << std::endl;
        return;
    }
    ::memmove(&body._buffer, &updateEcs, sizeof(updateEcs));
    for (auto &session : sessions)
    {
        std::shared_ptr<Message> message = std::make_shared<Message>();
        message->setMagicNumber(asChar(ActionCode::MAGIC_NUMBER));
        message->setAction(ecsInput);
        message->setEmmiterID(0x01);
        message->setBody(body);
        server_broker->addMessage(session->getId(), 1, message.get());
        std::cout << "Message sent to client <" << session->getId() << ">" << std::endl;
    }
}
