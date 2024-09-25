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
#include "ECS/SystemManager.hpp"

/**
 * @class Ecs
 * @brief The Ecs class is the main class of the ECS system. It is responsible for creating and destroying entities, and adding and removing components from entities
 */
class Ecs {
    public:
        /**
         * @brief Construct a new Ecs object
         */
        Ecs();

        /**
         * @brief Destroy the Ecs object
         */
        ~Ecs();

        /**
         * @brief Create a new entity
         * @return Entity The entity that was created
         */
        Entity createEntity();

        /**
         * @brief Create a new entity
         * @param entity The entity to create
         * @return Entity The entity that was created
         */
        Entity createEntity(Entity entity);

        /**
         * @brief Destroy an entity
         * @param entity The entity to destroy
         */
        void destroyEntity(Entity entity);

        /**
         * @brief Register a component
         * @tparam T The component to register
         */
        template <typename T>
        void registerComponent()
        {
            _componentManager->registerComponent<T>();
        }

        /**
         * @brief Add a component to an entity
         * @tparam T The component to add
         * @param entity The entity to add the component to
         * @param component The component to add
         */
        template <typename T>
        void addComponent(Entity entity, T component)
        {
            _componentManager->addComponent<T>(entity, component);
            auto signature = _entityManager->getSignature(entity);
            signature.set(_componentManager->getComponentType<T>(), true);
            _entityManager->setSignature(entity, signature);
            _systemManager->entitySignatureChanged(entity, signature);
        }

        /**
         * @brief Remove a component from an entity
         * @tparam T The component to remove
         * @param entity The entity to remove the component from
         */
        template <typename T>
        void removeComponent(Entity entity)
        {
            _componentManager->removeComponent<T>(entity);
            auto signature = _entityManager->getSignature(entity);
            signature.set(_componentManager->getComponentType<T>(), false);
            _entityManager->setSignature(entity, signature);
            _systemManager->entitySignatureChanged(entity, signature);
        }

        /**
         * @brief Get a component from an entity
         * @tparam T The component to get
         * @param entity The entity to get the component from
         * @return T& The component
         */
        template <typename T>
        T &getComponent(Entity entity)
        {
            return _componentManager->getComponent<T>(entity);
        }

        /**
         * @brief Get a component type
         * @tparam T The component to get the type of
         * @return ComponentType The component type
         */
        template <typename T>
        ComponentType getComponentType()
        {
            return _componentManager->getComponentType<T>();
        }

        /**
         * @brief Registers a new system of type T.
         *
         * This function registers a new system with the system manager and returns a shared pointer to the newly registered system.
         *
         * @tparam T The type of the system to be registered.
         * @return std::shared_ptr<T> A shared pointer to the newly registered system.
         */
        template <typename T>
        std::shared_ptr<T> registerSystem()
        {
            return _systemManager->registerSystem<T>();
        }

        /**
         * @brief Set the signature of a system
         *
         * @tparam T The system to set the signature of
         * @param signature The signature to set
         */
        template <typename T>
        void setSignature(Signature signature)
        {
            _systemManager->setSignature<T>(signature);
        }

        /**
         * @brief Update the ECS
         *
         * This function will be used to update the ECS by calling the update function of the system manager
         * @param dt The delta time
         */
        void update(float dt);
    private:
        std::unique_ptr<ComponentManager> _componentManager;        ///< The component manager
        std::unique_ptr<EntityManager> _entityManager;              ///< The entity manager
        std::unique_ptr<SystemManager> _systemManager;              ///< The system manager
};