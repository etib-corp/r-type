/*
** EPITECH PROJECT, 2024
** client
** File description:
** Ecs
*/

#pragma once

#include "ECS/common.hpp"
#include "ECS/ComponentManager.hpp"
#include "ECS/EntityManager.hpp"

class Ecs {
    public:
        Ecs();
        ~Ecs();

        Entity createEntity();

        void destroyEntity(Entity entity);

        template <typename T>
        void registerComponent() {
            _componentManager->registerComponent<T>();
        }

        template <typename T>
        void addComponent(Entity entity, T component) {
            _componentManager->addComponent<T>(entity, component);
            auto signature = _entityManager->getSignature(entity);
            signature.set(_componentManager->getComponentType<T>(), true);
            _entityManager->setSignature(entity, signature);
        }

        template <typename T>
        void removeComponent(Entity entity) {
            _componentManager->removeComponent<T>(entity);
            auto signature = _entityManager->getSignature(entity);
            signature.set(_componentManager->getComponentType<T>(), false);
            _entityManager->setSignature(entity, signature);
        }

        template <typename T>
        T &getComponent(Entity entity) {
            return _componentManager->getComponent<T>(entity);
        }

        template <typename T>
        ComponentType getComponentType() {
            return _componentManager->getComponentType<T>();
        }
    private:
        std::unique_ptr<ComponentManager> _componentManager;
        std::unique_ptr<EntityManager> _entityManager;
};