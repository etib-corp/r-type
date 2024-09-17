/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LoaderLib
*/


#ifndef LOADERLIB_HPP_
#define LOADERLIB_HPP_

#include <iostream>
#include <dlfcn.h>

#include <memory>

#ifdef __linux__
    #define LOAD_SYM(lib, var, sym, type) \
        if ((type)dlsym(lib->_handles[path], sym) != NULL) \
                var = (type)dlsym(lib->_handles[path], sym);
#endif // __linux__

class LoaderLib {
    public:
        LoaderLib(const std::string& NetworkModule, const std::string& CoreModule);
        ~LoaderLib();

        bool load();

    protected:
        const std::string _pathNetworkModule;
        const std::string _pathCoreModule;
    private:
};

#endif /* !LOADERLIB_HPP_ */
