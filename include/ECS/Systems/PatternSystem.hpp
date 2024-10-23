/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** PaternSystem
*/

#ifndef PATTERNSYSTEM_HPP_
#define PATTERNSYSTEM_HPP_

#include "ECS/SystemManager.hpp"
#include <functional>
#include <map>
#include "ECS/Components/PatternComponent.hpp"

class PatternSystem : public System {
    public:
        PatternSystem();

        ~PatternSystem();

        void update(Ecs *ecs, float dt) override;

        bool addPattern(const std::string &name, std::function<void(PatternComponent& pattern, TransformComponent& transform)> pattern)
        {
            _patterns[name] = pattern;
            return true;
        }

    protected:
    private:
        std::map<std::string, std::function<void(PatternComponent& pattern, TransformComponent& transform)>> _patterns;
};

#endif /* !PATTERNSYSTEM_HPP_ */
