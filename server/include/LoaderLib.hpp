/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LoaderLib
*/


#ifndef LOADERLIB_HPP_
#define LOADERLIB_HPP_

#include <iostream>
#include <exception>
#include <memory>
#include <map>
#include <functional>
#include "interface/INetworkModule.hpp"

#ifdef __linux__
    #include <dlfcn.h>

    #define OPEN_SYM(path, var) \
        var = dlopen(path.c_str(), RTLD_LAZY)

    #define LOAD_SYM(libHandle, var, sym, type) \
        if ((type)dlsym(libHandle, sym) != NULL) \
                var = (type)dlsym(libHandle, sym);
#endif // __linux__

#ifdef __WIN32
    #include <windows.h>

    #define OPEN_SYM()

    #define LOAD_SYM()

#endif

class LoaderLibError : public std::exception {
    public:
        LoaderLibError(const std::string& message): _message(message) {};
        const char *what() const noexcept override { return _message.c_str(); }

    protected:
        std::string _message;
};

/**
 * @class LoaderLib
 * @brief The LoaderLib class is responsible for loading network and core modules dynamically.
 *
 * The LoaderLib class provides functionality to load network and core modules dynamically. It allows creating network modules and checking if the modules are currently being loaded.
 *
 * @note This class assumes that the network and core modules are implemented using the INetworkModule interface.
 */
class LoaderLib {
    public:
        /**
         * @brief Constructs a LoaderLib object with the specified network module and core module.
         *
         * @param NetworkModule The path to the network module.
         * @param CoreModule The path to the core module.
         */
        LoaderLib(const std::string& NetworkModule, const std::string& CoreModule);
        ~LoaderLib();
        /**
         * @brief Checks if the loader is currently loading.
         *
         * This function checks if the loader is currently loading by attempting to load the network module.
         * If the network module fails to load, an exception of type LoaderLibError is thrown with the corresponding error message.
         *
         * @throws LoaderLibError If the network module fails to load.
         */
        void LoadModule(void);

        /**
         * @brief Creates a network module.
         *
         * @return Pointer to an INetworkModule object.
         */
        INetworkModule *createNetworkModule(void);

    protected:
        std::string _pathNetworkModule;
        std::string _pathCoreModule;

        std::function<INetworkModule*()> _createNetworkModule;

        void *_handleNetworkModule;
        void *_handleCoreModule;
    private:
};

#endif /* !LOADERLIB_HPP_ */
