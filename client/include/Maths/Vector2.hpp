/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Vector2
*/

#pragma once

#include "Error.hpp"
#include <glm.hpp>

#include <cmath>
#include <iostream>
#include <memory>
#include <type_traits>

namespace LE {
    /**
     * @brief A 2D vector class template.
     *
     * This class represents a 2D vector with x and y components.
     * @tparam T The type of the vector components.
     * @note The template parameter T must be an arithmetic type.
     */
    template <typename T>
    requires std::is_arithmetic<T>::value
    class Vector2 {
        public:
            /**
             * @brief An exception class for Vector2 errors.
             *
             * This class is used to throw exceptions when an error occurs in the Vector2 class.
             * The error message is passed as a parameter to the constructor.
             * The error message can be retrieved using the what() method.
            */
            class Vector2Error : public LE::Error {
                public:
                    /**
                     * @brief Constructs a Vector2Error object with the specified error message.
                     *
                     * @param message The error message.
                     */
                    Vector2Error(const std::string &message) : Error(message) {}
            };

            /**
             * @brief Constructs a Vector2 object with default x and y components.
             *
             * The default x and y components are set to 0.
            */
            Vector2()
            {
                this->x = static_cast<T>(0);
                this->y = static_cast<T>(0);
            }
            /**
             * @brief Constructs a Vector2 object with specified x and y components.
             *
             * @param x The x component of the vector.
             * @param y The y component of the vector.
             */
            Vector2(const T& x, const T& y) : x(x), y(y) {}

            /**
             * @brief Constructs a Vector2 object from the specified glm::vec2 object.
             *
             * @param vec The glm::vec2 object.
            */
            Vector2(const glm::vec2& vec) : x(vec.x), y(vec.y) {}

            /**
             * @brief Destructor for the Vector2 object.
             */
            ~Vector2() = default;

            /**
             * @brief Returns the length of the vector.
             *
             * @return The length of the vector.
            */
            double length() const
            {
                return sqrt(this->x * this->x + this->y * this->y);
            }

            /**
             * @brief Returns the distance between this vector and another vector.
             *
             * @param other The other vector.
             * @return The distance between this vector and the other vector.
            */
            double distance(const Vector2<T>& other) const
            {
                return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
            }

            /**
             * @brief Returns the dot product of this vector and another vector.
             *
             * @param other The other vector.
             * @return The dot product of this vector and the other vector.
            */
            double dot(const Vector2<T>& other) const
            {
                return this->x * other.x + this->y * other.y;
            }

            /**
             * @brief Returns the cross product of this vector and another vector.
             *
             * @param other The other vector.
             * @return The cross product of this vector and the other vector.
            */
            Vector2<T> cross(const Vector2<T>& other) const
            {
                return Vector2<T>(this->y * other.x - this->x * other.y, this->x * other.y - this->y * other.x);
            }

            /**
             * @brief Returns the normalized vector.
             *
             * @return The normalized vector.
            */
            Vector2<T> normalize() const
            {
                double len = length();
                if (len == 0)
                throw Vector2Error("Cannot normalize a vector with length 0.");
                return Vector2<T>(this->x / len, this->y / len);
            }

            /**
             * @brief Returns the face forward vector.
             *
             * @param n The normal vector.
             * @return The face forward vector.
            */
            Vector2<T> faceForward(const Vector2<T>& n) const
            {
                return dot(n) < 0 ? n : n * -1;
            }

            /**
             * @brief Returns the reflection vector.
             *
             * @param n The normal vector.
             * @return The reflection vector.
            */
            Vector2<T> reflect(const Vector2<T>& n) const
            {
                return *this - n * (2 * dot(n));
            }

            /**
             * @brief Returns the refraction vector.
             *
             * @param n The normal vector.
             * @param eta The refraction index.
            */
            Vector2<T> refract(const Vector2<T>& n, double eta) const
            {
                double k = 1.0 - eta * eta * (1.0 - dot(n) * dot(n));
                if (k < 0.0)
                    return Vector2<T>();
                else
                    return *this * eta - n * (eta * dot(n) + sqrt(k));
            }

            /**
             * @brief Returns the Vector2 object as a glm::vec2 object.
             *
             * @return The Vector2 object as a glm::vec2 object.
            */
            glm::vec2 toGlmVec2() const
            {
                return glm::vec2(this->x, this->y);
            }

            /**
             * @brief Returns the sum of this vector and another vector.
             *
             * @param other The other vector.
             * @return The sum of this vector and the other vector.
            */
            Vector2<T> operator+(const Vector2<T>& other) const
            {
                return Vector2<T>(this->x + other.x, this->y + other.y);
            }

            /**
             * @brief Adds another vector to this vector.
             *
             * @param other The other vector.
            */
            void operator+=(const Vector2<T>& other)
            {
                this->x += other.x;
                this->y += other.y;
            }

            /**
             * @brief Returns the difference between this vector and another vector.
             *
             * @param other The other vector.
             * @return The difference between this vector and the other vector.
            */
            Vector2<T> operator-(const Vector2<T>& other) const
            {
                return Vector2<T>(this->x - other.x, this->y - other.y);
            }

            /**
             * @brief Negates this vector.
             *
             * @return The negated vector.
            */
            Vector2<T> operator-() const
            {
                return Vector2<T>(-this->x, -this->y);
            }

            /**
             * @brief Subtracts another vector from this vector.
             *
             * @param other The other vector.
            */
            void operator-=(const Vector2<T>& other)
            {
                this->x -= other.x;
                this->y -= other.y;
            }

            /**
             * @brief Returns the product of this vector and a scalar.
             *
             * @param scalar The scalar.
             * @return The product of this vector and the scalar.
            */
            Vector2<T> operator*(const T& scalar) const
            {
                return Vector2<T>(this->x * scalar, this->y * scalar);
            }

            /**
             * @brief Multiplies this vector by a scalar.
             *
             * @param scalar The scalar.
            */
            void operator*=(const T& scalar)
            {
                this->x *= scalar;
                this->y *= scalar;
            }

            /**
             * @brief Returns the division of this vector by a scalar.
             *
             * @param scalar The scalar.
             * @return The division of this vector by the scalar.
            */
            Vector2<T> operator/(const T& scalar) const
            {
                if (scalar == 0)
                    throw Vector2Error("Cannot divide by zero");
                return Vector2<T>(this->x / scalar, this->y / scalar);
            }

            /**
             * @brief Divides this vector by a scalar.
             *
             * @param scalar The scalar.
            */
            void operator/=(const T& scalar)
            {
                if (scalar == 0)
                    throw Vector2Error("Cannot divide by zero");
                this->x /= scalar;
                this->y /= scalar;
            }

            /**
             * @brief Returns true if this vector is equal to another vector.
             *
             * @param other The other vector.
             * @return True if this vector is equal to the other vector, false otherwise.
            */
            bool operator==(const Vector2<T>& other) const
            {
                return this->x == other.x && this->y == other.y;
            }

            /**
             * @brief Returns true if this vector is not equal to another vector.
             *
             * @param other The other vector.
             * @return True if this vector is not equal to the other vector, false otherwise.
            */
            bool operator!=(const Vector2<T>& other) const
            {
                return this->x != other.x || this->y != other.y;
            }

            /**
             * @brief Returns the component of the vector at the specified index.
             *
             * @param index The index of the component.
             * @return The component of the vector at the specified index.
             * @throws Vector2Error if the index is out of range.
            */
            T& operator[](int index)
            {
                if (index == 0)
                    return this->x;
                else if (index == 1)
                    return this->y;
                else
                    throw Vector2Error("Index out of range");
            }

            /**
             * @brief Returns the component of the vector at the specified index.
             *
             * @param index The index of the component.
             * @return The component of the vector at the specified index.
             * @throws Vector2Error if the index is out of range.
            */
            const T& operator[](int index) const
            {
                if (index == 0)
                    return this->x;
                else if (index == 1)
                    return this->y;
                else
                    throw Vector2Error("Index out of range");
            }

            T x; /**< The x component of the vector. */
            T y; /**< The y component of the vector. */
    };
}

/**
 * @brief Outputs the vector to the output stream.
 *
 * @param os The output stream.
 * @param vec The vector to output.
 * @return The output stream.
*/
template<typename T>
std::ostream& operator<<(std::ostream& os, const LE::Vector2<T> vec)
{
    const char* name = typeid(T).name();
    os << "Vector2<" << name << ">(" << vec.x << ", " << vec.y << ")";
    return os;
}