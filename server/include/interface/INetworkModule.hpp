/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ANetworkModule
*/

#ifndef ANETWORKMODULE_HPP_
#define ANETWORKMODULE_HPP_

/**
 * @class INetworkModule
 * @brief Abstract base class for network modules.
 *
 * This class defines the interface for network modules, providing a pure virtual
 * function `run` that must be implemented by derived classes. It also includes
 * a virtual destructor to ensure proper cleanup of derived classes.
 */
class INetworkModule {
    public:
        virtual ~INetworkModule() = default;

        virtual void run() = 0;

    protected:
    private:
};

#endif /* !ANETWORKMODULE_HPP_ */
