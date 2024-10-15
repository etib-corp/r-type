/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ResponsibilityChain
*/

#ifndef RESPONSIBILITYCHAIN_HPP_
#define RESPONSIBILITYCHAIN_HPP_

#include <iostream>
#include <vector>
#include "PackUnpack.hpp"
#include "ECS/Ecs.hpp"

using CallBackFunc = std::function<bool(const Request&, std::shared_ptr<Ecs>)>;

class ResponsibilityChain {
    public:
        void setActionCallback(char action, const std::vector<CallBackFunc>& callbacks)
        {
            _actionCallbacks[action] = callbacks;
        }

        void addActionCallback(char action, const CallBackFunc& callback)
        {
            _actionCallbacks[action].push_back(callback);
        }

        [[nodiscard]] std::vector<CallBackFunc> getActionCallbacks(char action) const
        {
            auto it = _actionCallbacks.find(action);
            if (it != _actionCallbacks.end())
            {
                return it->second;
            }
            return {};
        }

        void clearActionCallbacks(char action)
        {
            _actionCallbacks.erase(action);
        }

    private:
        std::unordered_map<char, std::vector<CallBackFunc>> _actionCallbacks;
};

#endif /* !RESPONSIBILITYCHAIN_HPP_ */
