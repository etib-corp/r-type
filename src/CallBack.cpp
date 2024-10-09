/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CallBack
*/

#include "SenToAllClient.hpp"
#include "CallBack.hpp"

void executeCallbacks(
    const std::vector<std::function<void(
        const Header&, std::shared_ptr<Ecs>
    )>>& callbacks,
    const Header& header,
    std::shared_ptr<Ecs> _ecs
)
{
    for (const auto& callback : callbacks)
    {
        std::cout << header.Action << std::endl;
        callback(header, _ecs);
    }
}

void processHeader(const Header& header, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain)
{
    auto callbacks = chain.getActionCallbacks(header.Action);

    for (const auto& callback : callbacks)
    {
        callback(header, _ecs);
    }
}
