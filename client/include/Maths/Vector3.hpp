/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Vector3
*/


#include "Error.hpp"
#include <glm.hpp>

#include <cmath>
#include <cxxabi.h>
#include <iostream>
#include <memory>
#include <type_traits>

namespace LE {
    /**
     * @brief A 3D vector class template.
     *
     * This class represents a 3D vector with x, y, and z components.
     * @tparam T The type of the components of the vector.
     * @note The template parameter T must be an arithmetic type.
     */
    template <typename T>
    requires std::is_arithmetic<T>::value
    class Vector3 {
        public:
            class Vector3Error : public Error {
                public:
                    Vector3Error(const std::string &message) : Error(message) {}
            };

            /**
             * @brief Constructs a Vector3 object with default x, y and z components.
             *
             * The default x, y and z components are set to 0.
            */
            Vector3()
            {
                this->x = static_cast<T>(0);
                this->y = static_cast<T>(0);
                this->z = static_cast<T>(0);
            }
            /**
             * @brief Constructs a Vector3 object with specified x, y and z components.
             *
             * @param x The x component of the vector.
             * @param y The y component of the vector.
             * @param z The z component of the vector.
             */
            Vector3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

            /**
             * @brief Constructs a Vector3 object from the specified glm::vec3 object.
             *
             * @param vec The glm::vec3 object.
             */
            Vector3(const glm::vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {}

            /**
             * @brief Destructor for the Vector3 object.
             */
            ~Vector3() {}

            /**
             * @brief Returns the length of the vector.
             *
             * @return The length of the vector.
            */
            double length() const
            {
                return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
            }

            /**
             * @brief Returns the distance between this vector and another vector.
             *
             * @param other The other vector.
             * @return The distance between this vector and the other vector.
            */
            double distance(const Vector3<T>& other) const
            {
                return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2));
            }

            /**
             * @brief Returns the dot product of this vector and another vector.
             *
             * @param other The other vector.
             * @return The dot product of this vector and the other vector.
            */
            double dot(const Vector3<T>& other) const
            {
                return this->x * other.x + this->y * other.y + this->z * other.z;
            }

            /**
             * @brief Returns the cross product of this vector and another vector.
             *
             * @param other The other vector.
             * @return The cross product of this vector and the other vector.
            */
            Vector3<T> cross(const Vector3<T>& other) const
            {
                return Vector3<T>(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
            }

            /**
             * @brief Returns the normalized version of this vector.
             *
             * @return The normalized version of this vector.
            */
            Vector3<T> normalize() const
            {
                double len = length();
                if (len == 0)
                    throw Vector3Error("Cannot normalize a vector with length 0.");
                return Vector3<T>(this->x / len, this->y / len, this->z / len);
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
             * @brief Returns the Vector3 object as a glm::vec3 object.
             *
             * @return The Vector3 object as a glm::vec3 object.
            */
            glm::vec3 toGlmVec3() const
            {
                return glm::vec3(this->x, this->y, this->z);
            }

            /**
             * @brief Returns the sum of this vector and another vector.
             *
             * @param other The other vector.
             * @return The sum of this vector and the other vector.
            */
            Vector3<T> operator+(const Vector3<T>& other) const
            {
                return Vector3<T>(this->x + other.x, this->y + other.y, this->z + other.z);
            }

            /**
             * @brief Adds another vector to this vector.
             *
             * @param other The other vector.
            */
            void operator+=(const Vector3<T>& other)
            {
                this->x += other.x;
                this->y += other.y;
                this->z += other.z;
            }

            /**
             * @brief Returns the difference of this vector and another vector.
             *
             * @param other The other vector.
             * @return The difference of this vector and the other vector.
            */
            Vector3<T> operator-(const Vector3<T>& other) const
            {
                return Vector3<T>(this->x - other.x, this->y - other.y, this->z - other.z);
            }

            /**
             * @brief Negate this vector.
             *
             * @return The negated vector.
            */
            Vector3<T> operator-() const
            {
                return Vector3<T>(-this->x, -this->y, -this->z);
            }

            /**
             * @brief Subtracts another vector from this vector.
             *
             * @param other The other vector.
            */
            void operator-=(const Vector3<T>& other)
            {
                this->x -= other.x;
                this->y -= other.y;
                this->z -= other.z;
            }

            /**
             * @brief Returns the product of this vector and a scalar.
             *
             * @param scalar The scalar.
             * @return The product of this vector and the scalar.
            */
            Vector3<T> operator*(const T& scalar) const
            {
                return Vector3<T>(this->x * scalar, this->y * scalar, this->z * scalar);
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
            }

            /**
             * @brief Returns the division of this vector by a scalar.
             *
             * @param scalar The scalar.
             * @return The division of this vector by the scalar.
            */
            Vector3<T> operator/(const T& scalar) const
            {
                if (scalar == 0)
                    throw Vector3Error("Cannot divide by zero.");
                return Vector3<T>(this->x / scalar, this->y / scalar, this->z / scalar);
            }

            /**
             * @brief Divides this vector by a scalar.
             *
             * @param scalar The scalar.
            */
            void operator/=(const T& scalar)
            {
                if (scalar == 0)
                    throw Vector3Error("Cannot divide by zero.");
                this->x /= scalar;
                this->y /= scalar;
                this->z /= scalar;
            }

            /**
             * @brief Returns true if this vector is equal to another vector.
             *
             * @param other The other vector.
             * @return True if this vector is equal to the other vector, false otherwise.
            */
            bool operator==(const Vector3<T>& other) const
            {
                return this->x == other.x && this->y == other.y && this->z == other.z;
            }

            /**
             * @brief Returns true if this vector is not equal to another vector.
             *
             * @param other The other vector.
             * @return True if this vector is not equal to the other vector, false otherwise.
            */
            bool operator!=(const Vector3<T>& other) const
            {
                return this->x != other.x || this->y != other.y || this->z != other.z;
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
                if (index == 1)
                    return this->y;
                if (index == 2)
                    return this->z;
                throw Vector3Error("Index out of range");
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
                if (index == 1)
                    return this->y;
                if (index == 2)
                    return this->z;
                throw Vector3Error("Index out of range");
            }


            T x; /**< The x component of the vector. */
            T y; /**< The y component of the vector. */
            T z; /**< The z component of the vector. */
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
std::ostream& operator<<(std::ostream& os, const LE::Vector3<T> vec)
{
    const char* name = typeid(T).name();
    int status = -4;

    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    name = status == 0 ? res.get() : typeid(T).name();

    os << "Vector3<" << name << ">(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}