/*
** EPITECH PROJECT, 2024
** client
** File description:
** ComponentManager
*/

#pragma once

#include "ECS/common.hpp"

class ComponentManagerError : public LE::Error {
    public:
        ComponentManagerError(const std::string &message): Error(message) {}
};

class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {
    public:
        ComponentArray() {
            // _components.fill(nullptr);
            _entityToIndexMap.clear();
            _indexToEntityMap.clear();
            _size = 0;
        }
        ~ComponentArray() = default;

        void insertData(Entity entity, T component) {
            if (_entityToIndexMap.find(entity) != _entityToIndexMap.end()) {
                throw ComponentManagerError("Component already exists");
            }
            _components[_size] = component;
            _entityToIndexMap[entity] = _size;
            _indexToEntityMap[_size] = entity;
            _size++;
        }

        void removeData(Entity entity) {
            if (_entityToIndexMap.find(entity) == _entityToIndexMap.end()) {
                throw ComponentManagerError("Removing non-existent component");
            }

            size_t indexOfRemovedEntity = _entityToIndexMap[entity];
            size_t indexOfLastElement = _size - 1;
            _components[indexOfRemovedEntity] = _components[indexOfLastElement];

            Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];
            _entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            _indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            _entityToIndexMap.erase(entity);
            _indexToEntityMap.erase(indexOfLastElement);

            _size--;
        }

        T &getData(Entity entity) {
            if (_entityToIndexMap.find(entity) == _entityToIndexMap.end()) {
                throw ComponentManagerError("Retrieving non-existent component");
            }

            return _components[_entityToIndexMap[entity]];
        }

        void entityDestroyed(Entity entity) {
            if (_entityToIndexMap.find(entity) != _entityToIndexMap.end()) {
                removeData(entity);
            }
        }

    private:
        std::array<T, MAX_ENTITIES> _components;
        std::unordered_map<Entity, size_t> _entityToIndexMap;
        std::unordered_map<size_t, Entity> _indexToEntityMap;
        size_t _size;
};

class ComponentManager {
    public:
        ComponentManager() {
            _nextComponentType = 0;
        }
        ~ComponentManager() {}

        template <typename T>
        bool registerComponent() {
            std::string typeName = typeid(T).name();
            if (_componentArrays.find(typeName) != _componentArrays.end()) {
                throw ComponentManagerError("Component already registered");
            }
            _componentArrays[typeName] = std::make_unique<ComponentArray<T>>();
            _componentTypes[typeName] = _nextComponentType;
            _nextComponentType++;
            return true;
        }

        template <typename T>
        void addComponent(Entity entity, T component) {
            getComponentArray<T>()->insertData(entity, component);
        }

        template <typename T>
        void removeComponent(Entity entity) {
            getComponentArray<T>()->removeData(entity);
        }

        template <typename T>
        T &getComponent(Entity entity) {
            return getComponentArray<T>()->getData(entity);
        }

        template <typename T>
        ComponentType getComponentType() {
            std::string typeName = typeid(T).name();
            if (_componentTypes.find(typeName) == _componentTypes.end()) {
                throw ComponentManagerError("Component not registered before use");
            }
            return _componentTypes[typeName];
        }

        void entityDestroyed(Entity entity) {
            for (auto const &pair : _componentArrays) {
                auto const &component = pair.second;
                component->entityDestroyed(entity);
            }
        }

    private:
        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray() {
            std::string typeName = typeid(T).name();
            if (_componentArrays.find(typeName) == _componentArrays.end()) {
                throw ComponentManagerError("Component not registered before use");
            }
            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
        }

        std::unordered_map<std::string, std::shared_ptr<IComponentArray>> _componentArrays;
        std::unordered_map<std::string, ComponentType> _componentTypes;
        unsigned int _nextComponentType;
};