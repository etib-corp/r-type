/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Vector4
*/

#pragma once

#include "Error.hpp"
#include <glm.hpp>
#include "Vector3.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <type_traits>

namespace LE {
    /**
     * @brief A 4D vector class template.
     *
     * This class represents a 4D vector with x, y, z and w components.
     * @tparam T The type of the components of the vector.
     * @note The template parameter T must be an arithmetic type.
     */
    template <typename T>
    // requires std::is_arithmetic<T>::value
    class Vector4 {
        public:
            class Vector4Error : public Error {
                public:
                    Vector4Error(const std::string &message) : Error(message) {}
            };

            /**
             * @brief Constructs a Vector4 object with default x, y, z and w components.
             *
             * The default x and y components are set to 0.
             */
            Vector4()
            {
                this->x = static_cast<T>(0);
                this->y = static_cast<T>(0);
                this->z = static_cast<T>(0);
                this->w = static_cast<T>(0);
            }

            /**
             * @brief Constructs a Vector4 object with specified x, y, z and w components.
             *
             * @param x The x component of the vector.
             * @param y The y component of the vector.
             * @param z The z component of the vector.
             * @param w The w component of the vector.
             */
            Vector4(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}

            /**
             * @brief Constructs a Vector4 object from the specified glm::vec4 object.
             *
             * @param vec The glm::vec4 object.
             */
            Vector4(const glm::vec4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}


            /**
             * @brief Destructor for the Vector4 object.
             */
            ~Vector4() {}

            /**
             * @brief Returns the length of the vector.
             *
             * @return The length of the vector.
            */
            double length() const
            {
                return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
            }

            /**
             * @brief Returns the distance between this vector and another vector.
             *
             * @param other The other vector.
             * @return The distance between this vector and the other vector.
            */
            double distance(const Vector4<T>& other) const
            {
                return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2) + pow(this->w - other.w, 2));
            }

            /**
             * @brief Returns the dot product of this vector and another vector.
             *
             * @param other The other vector.
             * @return The dot product of this vector and the other vector.
            */
            double dot(const Vector4<T>& other) const
            {
                return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
            }

            /**
             * @brief Returns the cross product of this vector and another vector.
             *
             * @param other The other vector.
             * @return The cross product of this vector and the other vector.
            */
            Vector4<T> cross(const Vector4<T>& other) const
            {
                return Vector4<T>(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x, 0);
            }

            /**
             * @brief Normalizes the vector.
             *
             * @return The normalized vector.
            */
            Vector4<T> normalize() const
            {
                double len = this->length();
                if (len == 0)
                    throw Vector4Error("Cannot normalize a vector with length 0.");
                return Vector4<T>(this->x / len, this->y / len, this->z / len, this->w / len);
            }

            /**
             * @brief Returns the face forward vector.
             *
             * @param n The normal vector.
             * @return The face forward vector.
            */
            Vector3<T> faceForward(const Vector3<T>& n) const
            {
                return dot(n) < 0 ? n : n * -1;
            }

            /**
             * @brief Returns the reflection vector.
             *
             * @param n The normal vector.
             * @return The reflection vector.
            */
            Vector3<T> reflect(const Vector3<T>& n) const
            {
                return *this - n * (2 * dot(n));
            }

            /**
             * @brief Returns the refraction vector.
             *
             * @param n The normal vector.
             * @param eta The refraction index.
            */
            Vector3<T> refract(const Vector3<T>& n, double eta) const
            {
                double k = 1.0 - eta * eta * (1.0 - dot(n) * dot(n));
                if (k < 0.0)
                    return Vector3<T>();
                else
                    return *this * eta - n * (eta * dot(n) + sqrt(k));
            }

            /**
             * @brief Returns the Vector4 object as a glm::vec4 object.
             *
             * @return The Vector4 object as a glm::vec4 object.
            */
            glm::vec4 toGlmVec4() const
            {
                return glm::vec4(this->x, this->y, this->z, this->w);
            }

            /**
             * @brief Returns the sum of this vector and another vector.
             *
             * @param other The other vector.
             * @return The sum of this vector and the other vector.
            */
            Vector4<T> operator+(const Vector4<T>& other) const
            {
                return Vector4<T>(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
            }

            /**
             * @brief Adds another vector to this vector.
             *
             * @param other The other vector.
            */
            void operator+=(const Vector4<T>& other)
            {
                this->x += other.x;
                this->y += other.y;
                this->z += other.z;
                this->w += other.w;
            }

            /**
             * @brief Returns the difference of this vector and another vector.
             *
             * @param other The other vector.
             * @return The difference of this vector and the other vector.
            */
            Vector4<T> operator-(const Vector4<T>& other) const
            {
                return Vector4<T>(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
            }

            /**
             * @brief Negate this vector.
             *
             * @return The negated vector.
            */
            Vector4<T> operator-() const
            {
                return Vector4<T>(-this->x, -this->y, -this->z, -this->w);
            }

            /**
             * @brief Subtracts another vector from this vector.
             *
             * @param other The other vector.
            */
            void operator-=(const Vector4<T>& other)
            {
                this->x -= other.x;
                this->y -= other.y;
                this->z -= other.z;
                this->w -= other.w;
            }

            /**
             * @brief Returns the product of this vector and a scalar.
             *
             * @param scalar The scalar.
             * @return The product of this vector and the scalar.
            */
            Vector4<T> operator*(const T& scalar) const
            {
                return Vector4<T>(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
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
                this->z *= scalar;
                this->w *= scalar;
            }

            /**
             * @brief Returns the division of this vector by a scalar.
             *
             * @param scalar The scalar.
             * @return The division of this vector by the scalar.
            */
            Vector4<T> operator/(const T& scalar) const
            {
                if (scalar == 0)
                    throw Vector4Error("Cannot divide by 0.");
                return Vector4<T>(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
            }

            /**
             * @brief Divides this vector by a scalar.
             *
             * @param scalar The scalar.
            */
            void operator/=(const T& scalar)
            {
                if (scalar == 0)
                    throw Vector4Error("Cannot divide by 0.");
                this->x /= scalar;
                this->y /= scalar;
                this->z /= scalar;
                this->w /= scalar;
            }

                /**
             * @brief Returns true if this vector is equal to another vector.
             *
             * @param other The other vector.
             * @return True if this vector is equal to the other vector, false otherwise.
            */
            bool operator==(const Vector4<T>& other) const
            {
                return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
            }

            /**
             * @brief Returns true if this vector is not equal to another vector.
             *
             * @param other The other vector.
             * @return True if this vector is not equal to the other vector, false otherwise.
            */
            bool operator!=(const Vector4<T>& other) const
            {
                return this->x != other.x || this->y != other.y || this->z != other.z || this->w != other.w;
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
                else if (index == 2)
                    return this->z;
                else if (index == 3)
                    return this->w;
                else
                    throw Vector4Error("Index out of range.");
            }

            /**
             * @brief Returns the component of the vector at the specified index.
             *
             * @param index The index of the component.
             * @return The component of the vector at the specified index.
             * @throws Vector2Error if the index is out of range.
            */
            T& operator[](int index) const
            {
                if (index == 0)
                    return this->x;
                else if (index == 1)
                    return this->y;
                else if (index == 2)
                    return this->z;
                else if (index == 3)
                    return this->w;
                else
                    throw Vector4Error("Index out of range.");
            }

            T x; /**< The x component of the vector. */
            T y; /**< The y component of the vector. */
            T z; /**< The z component of the vector. */
            T w; /**< The w component of the vector. */
    };
}

/**
 * @brief Outputs the vector to the output stream.
 *
 * @param os The output stream.
 * @param vec The vector.
 * @return The output stream.
*/
template<typename T>
std::ostream& operator<<(std::ostream& os, const LE::Vector4<T> vec)
{
    const char* name = typeid(T).name();

    os << "Vector4<" << name << ">(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}