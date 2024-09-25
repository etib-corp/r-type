/*
** EPITECH PROJECT, 2024
** client
** File description:
** EntityManager
*/

#pragma once

#include "ECS/common.hpp"

/**
 * @class EntityManagerError
 * @brief EntityManagerError class
 */
class EntityManagerError : public LE::Error {
    public:
        /**
         * @brief Construct a new EntityManagerError object
         * @param message The message to display
         */
        EntityManagerError(const std::string &message): Error(message) {}
};

/**
 * @class EntityManager
 * @brief The EntityManager class is responsible for creating and destroying entities
 * The EntityManager class is responsible for creating and destroying entities
 */
class EntityManager {
   public:
        /**
         * @brief Construct a new EntityManager object
         */
        EntityManager();

        /**
         * @brief Destroy the EntityManager object
         */
        ~EntityManager();

        /**
         * @brief Create a new entity
         *
         * @return Entity The entity that was created
         */
        Entity createEntity(void);

        /**
         * @brief Create a new entity
         * This function will be used to create an entity a specific entity
         *
         * @param entity The entity to create
         * @return Entity The entity that was created
         */
        Entity createEntity(Entity entity);

        /**
         * @brief Destroy an entity
         * This function will be used to destroy an entity
         *
         * @param entity The entity to destroy
         */
        void destroyEntity(Entity entity);

        /**
         * @brief Set the signature of an entity
         * This function will be used to set the signature of an entity
         *
         * @param entity The entity to set the signature of
         * @param signature The signature to set
         */
        void setSignature(Entity entity, Signature signature);

        /**
         * @brief Get the signature of an entity
         * This function will be used to get the signature of an entity
         *
         * @param entity The entity to get the signature of
         * @return Signature The signature of the entity
         */
        Signature getSignature(Entity entity);

    private:
        std::queue<Entity> _availableEntities;              // Queue of available entities
        std::array<Signature, MAX_ENTITIES> _signatures;    // Array of signatures
        unsigned int _livingEntityCount;                    // Number of living entities

};