/*
** EPITECH PROJECT, 2024
** client
** File description:
** EntityManager
*/

#pragma once

#include "ECS/common.hpp"

class EntityManagerError : public LE::Error {
    public:
        EntityManagerError(const std::string &message): Error(message) {}
};

class EntityManager {
   public:
        EntityManager();
        ~EntityManager();

        Entity createEntity(void);

        void destroyEntity(Entity entity);

        void setSignature(Entity entity, Signature signature);

        Signature getSignature(Entity entity);

    private:
        std::queue<Entity> _availableEntities;
        std::array<Signature, MAX_ENTITIES> _signatures;
        unsigned int _livingEntityCount;

};