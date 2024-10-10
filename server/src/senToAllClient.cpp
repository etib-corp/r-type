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
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return;
    }
    ::memmove(&body._buffer, &updateEcs, sizeof(updateEcs));
    for (auto &session : sessions)
    {
        std::shared_ptr<Message> message = std::make_shared<Message>();
        std::cout << "Message sent to client <" << (int)session->getId() << ">" << std::endl;
        message->setMagicNumber(asChar(ActionCode::MAGIC_NUMBER));
        message->setAction(ecsInput);
        message->setEmmiterID(0x01);
        message->setBody(body);
        try {
            server_broker->addMessage(session->getId(), 1, message.get());
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
