/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <iostream>

template <typename Enumeration>
auto asChar(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

#endif /* !UTILS_HPP_ */
