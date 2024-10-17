/*
** EPITECH PROJECT, 2024
** client
** File description:
** ComponentManager
*/

#pragma once

#include "ECS/common.hpp"

/**
 * @class ComponentManagerError
 * @brief ComponentManagerError class
 *
 * This class is used to throw errors related to the ComponentManager class
 */
class ComponentManagerError : public LE::Error {
    public:
        /**
         * @brief Construct a new ComponentManagerError object
         *
         * @param message The error message
         */
        ComponentManagerError(const std::string &message): Error(message) {}
};

/**
 * @class IComponentArray
 * @brief IComponentArray class
 *
 * This class is an interface for the ComponentArray class
 * It has a virtual destructor and a pure virtual function entityDestroyed
 * This class is used to store the components of an entity
 */
class IComponentArray {
    public:
        /**
         * @brief Destroy the IComponentArray object
         *
         * This is a virtual destructor
         */
        virtual ~IComponentArray() = default;

        /**
         * @brief entityDestroyed pure virtual function
         *
         * This function is used to remove the component of an entity
         * @param entity The entity to remove the component from
         */
        virtual void entityDestroyed(Entity entity) = 0;
};

/**
 * @class ComponentArray
 * @brief ComponentArray class
 *
 * This class is used to store the components of an entity
 * It is a template class that inherits from IComponentArray
 * It has a constructor, a destructor, and functions to insert, remove, and get data
 * @tparam T The type of the component
 */
template <typename T>
class ComponentArray : public IComponentArray {
    public:
        /**
         * @brief Construct a new ComponentArray object
         *
         * This constructor initializes the size of the component array to 0 and fills the components array with nullptr
         */
        ComponentArray()
        {
            _entityToIndexMap.clear();
            _indexToEntityMap.clear();
            _size = 0;
        }

        /**
         * @brief Destroy the ComponentArray object
         */
        ~ComponentArray() = default;

        /**
         * @brief insertData function
         *
         * This function is used to insert a component into the component array
         * @param entity The entity to insert the component into
         * @param component The component to insert
         */
        void insertData(Entity entity, T component)
        {
            if (_entityToIndexMap.find(entity) != _entityToIndexMap.end()) {
                throw ComponentManagerError("Component already exists");
            }
            _components[_size] = component;
            _entityToIndexMap[entity] = _size;
            _indexToEntityMap[_size] = entity;
            _size++;
        }

        /**
         * @brief removeData function
         *
         * This function is used to remove a component from the component array
         * @param entity The entity to remove the component from
         */
        void removeData(Entity entity)
        {
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

        /**
         * @brief getData function
         *
         * This function is used to get the component of an entity
         * @param entity The entity to get the component from
         * @return T& The component of the entity
         */
        T &getData(Entity entity)
        {
            if (_entityToIndexMap.find(entity) == _entityToIndexMap.end()) {
                throw ComponentManagerError("Retrieving non-existent component");
            }

            return _components[_entityToIndexMap[entity]];
        }

        /**
         * @brief entityDestroyed function
         *
         * This function is used to remove the component of an entity
         * @param entity The entity to remove the component from
         */
        void entityDestroyed(Entity entity)
        {
            if (_entityToIndexMap.find(entity) != _entityToIndexMap.end()) {
                removeData(entity);
            }
        }

        std::vector<T> getComponents()
        {
            std::vector<T> components;
            for (size_t i = 0; i < _size; i++) {
                components.push_back(_components[i]);
            }
            return components;
        }

    private:
        std::array<T, MAX_ENTITIES> _components;                ///< An array of components
        std::unordered_map<Entity, size_t> _entityToIndexMap;   ///< A map of entities to indices
        std::unordered_map<size_t, Entity> _indexToEntityMap;   ///< A map of indices to entities
        size_t _size;                                           ///< The size of the component array
};

/**
 * @brief ComponentManager class
 *
 * This class is used to manage the components of an entity
 * It has a constructor, a destructor, and functions to register, add, remove, and get components
 */
class ComponentManager {
    public:
        /**
         * @brief Construct a new ComponentManager object
         *
         * This constructor initializes the next component type to 0
         */
        ComponentManager()
        {
            _nextComponentType = 0;
        }

        /**
         * @brief Destroy the ComponentManager object
         */
        ~ComponentManager() {}

        /**
         * @brief registerComponent function
         *
         * This function is used to register a component
         * @tparam T The type of the component
         * @return true If the component is registered successfully, false otherwise
         */
        template <typename T>
        bool registerComponent()
        {
            std::string typeName = typeid(T).name();
            if (_componentArrays.find(typeName) != _componentArrays.end()) {
                throw ComponentManagerError("Component already registered");
            }
            _componentArrays[typeName] = std::make_unique<ComponentArray<T>>();
            _componentTypes[typeName] = _nextComponentType;
            _nextComponentType++;
            return true;
        }

        /**
         * @brief addComponent function
         *
         * This function is used to add a component to an entity
         * @tparam T The type of the component
         * @param entity The entity to add the component to
         * @param component The component to add
         */
        template <typename T>
        void addComponent(Entity entity, T component)
        {
            getComponentArray<T>()->insertData(entity, component);
        }

        /**
         * @brief removeComponent function
         *
         * This function is used to remove a component from an entity
         * @tparam T The type of the component
         * @param entity The entity to remove the component from
         */
        template <typename T>
        void removeComponent(Entity entity)
        {
            getComponentArray<T>()->removeData(entity);
        }

        /**
         * @brief getComponent function
         *
         * This function is used to get the component of an entity
         * @tparam T The type of the component
         * @param entity The entity to get the component from
         * @return T& The component of the entity
         */
        template <typename T>
        T &getComponent(Entity entity)
        {
            return getComponentArray<T>()->getData(entity);
        }

        /**
         * @brief getComponentType function
         *
         * This function is used to get the component type of a component
         * @tparam T The type of the component
         * @return ComponentType The component type of the component
         */
        template <typename T>
        ComponentType getComponentType()
        {
            std::string typeName = typeid(T).name();
            if (_componentTypes.find(typeName) == _componentTypes.end()) {
                throw ComponentManagerError("Component not registered before use");
            }
            return _componentTypes[typeName];
        }

        /**
         * @brief entityDestroyed function
         *
         * This function is used to remove the components of an entity
         * @param entity The entity to remove the components from
         */
        void entityDestroyed(Entity entity)
        {
            for (auto const &pair : _componentArrays) {
                auto const &component = pair.second;
                component->entityDestroyed(entity);
            }
        }

        template <typename T>
        std::vector<T> getComponents()
        {
            return getComponentArray<T>()->getComponents();
        }

    private:
        /**
         * @brief getComponentArray function
         *
         * This function is used to get the component array of a component
         * @tparam T The type of the component
         * @return std::shared_ptr<ComponentArray<T>> The component array of the component
         */
        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray()
        {
            std::string typeName = typeid(T).name();
            if (_componentArrays.find(typeName) == _componentArrays.end()) {
                throw ComponentManagerError("Component not registered before use");
            }
            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
        }

        std::unordered_map<std::string, std::shared_ptr<IComponentArray>> _componentArrays;     ///< A map of component arrays
        std::unordered_map<std::string, ComponentType> _componentTypes;                         ///< A map of component types
        unsigned int _nextComponentType;                                                        ///< The next component type
};
