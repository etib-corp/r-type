/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Matrix
*/

#pragma once

// Engine include
#include "Error.hpp"
#include "glm.hpp"

// C++ include
#include <array>
#include <iostream>
#include <type_traits>

/**
 * @file Matrix.hpp
 * @brief Defines the Matrix class for representing 4D vectors.
 */
namespace LE {
        /**
         * @class Matrix
         * @brief A class for representing a matrix.
         *
         * The Matrix class represents a matrix with the specified width and height.
         * @tparam WIDTH The width of the matrix.
         * @tparam HEIGHT The height of the matrix.
         * @tparam T The type of the elements in the matrix.
         * @note The width and height must be greater than 0.
         * @note The type T must be an arithmetic type.
        */
        template<int WIDTH, int HEIGHT, typename T>
        // requires (WIDTH > 0 && HEIGHT > 0 && std::is_arithmetic<T>::value)
        class Matrix {
            public:
                /**
                 * @brief Represents an error that can occur in the Matrix class.
                 */
                class MatrixError : public Error {
                public:
                    /**
                     * @brief Constructs a MatrixError object with the specified error message.
                     * @param message The error message.
                     */
                    MatrixError(std::string const &message)
                        : Error(message) {};
                };

                /**
                 * @brief Constructs a Matrix object with all elements set to 0.
                 *
                 * The constructor initializes all elements of the matrix to 0.
                */
                Matrix()
                {
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            this->_matrix[i][j] = static_cast<T>(0);
                        }
                    }
                }

                /**
                 * @brief Constructs a Matrix object with the specified elements.
                 *
                 * The constructor initializes the matrix with the specified elements.
                 * @param matrix The elements to initialize the matrix with.
                */
                Matrix(std::array<std::array<T, WIDTH>, HEIGHT>& matrix)
                {
                    this->_matrix = matrix;
                }

                Matrix(T values[WIDTH * HEIGHT])
                {
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            this->_matrix[i][j] = values[i * WIDTH + j];
                        }
                    }
                }

                /**
                 * @brief Constructs a Matrix object from a glm::mat.
                 *
                 * The constructor initializes the matrix from a glm::mat.
                 * @param matrix The glm::mat to initialize the matrix with.
                */
                Matrix(glm::mat<WIDTH, HEIGHT, T> matrix)
                {
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            this->_matrix[i][j] = matrix[i][j];
                        }
                    }
                }

                /**
                 * @brief Constructs a Matrix object with all elements set to the specified value.
                 *
                 * The constructor initializes all elements of the matrix to the specified value.
                 * @param f The value to initialize the matrix with.
                */
                Matrix(T f)
                {
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            this->_matrix[i][j] = f;
                        }
                    }
                }

                /**
                 * @brief Destroys the Matrix object.
                */
                ~Matrix() = default;

                /**
                 * @brief Returns the width of the matrix.
                 *
                 * The function returns the width of the matrix.
                */
                int getWidth() const
                {
                    return WIDTH;
                }

                /**
                 * @brief Returns the height of the matrix.
                 *
                 * The function returns the height of the matrix.
                */
                int getHeight() const
                {
                    return HEIGHT;
                }

                /**
                 * @brief Returns the values of the matrix.
                 *
                 * The function returns the values of the matrix as a pointer to a C-style array.
                 * @return The values of the matrix.
                 * @note The caller is responsible for freeing the memory allocated for the array using delete[].
                */
                T *value_ptr() const
                {
                    T *ptr = new T[WIDTH * HEIGHT];

                    if (!ptr)
                        throw MatrixError("Failed to allocate memory for matrix values.");
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            ptr[i * WIDTH + j] = this->_matrix[i][j];
                        }
                    }
                    return ptr;
                }

                /**
                 * @brief Returns the transpose of the matrix.
                 *
                 * The function returns the transpose of the matrix.
                 * @return The transpose of the matrix.
                */
                Matrix<HEIGHT, WIDTH, T> transpose() const
                {
                    Matrix<HEIGHT, WIDTH, T> result;
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            result._matrix[j][i] = this->_matrix[i][j];
                        }
                    }
                    return result;
                }

                /**
                 * @brief Returns the determinant of the matrix.
                 *
                 * The function returns the determinant of the matrix.
                 * @return The determinant of the matrix.
                */
                double determinant() const
                {
                    if (WIDTH != HEIGHT) {
                        throw MatrixError("Matrix must be square to calculate determinant.");
                    }
                    if (WIDTH == 2) {
                        return this->_matrix[0][0] * this->_matrix[1][1] - this->_matrix[0][1] * this->_matrix[1][0];
                    }
                    double det = 0;
                    for (int i = 0; i < WIDTH; i++) {
                        Matrix<WIDTH - 1, HEIGHT - 1, T> submatrix;
                        for (int j = 1; j < HEIGHT; j++) {
                            for (int k = 0; k < WIDTH; k++) {
                                if (k < i) {
                                    submatrix[j - 1][k] = this->_matrix[j][k];
                                } else if (k > i) {
                                    submatrix[j - 1][k - 1] = this->_matrix[j][k];
                                }
                            }
                        }
                        det += this->_matrix[0][i] * submatrix.determinant() * (i % 2 == 0 ? 1 : -1);
                    }
                    return det;
                }

                /**
                 * @brief Returns the Matrix as a glm::mat.
                 *
                 * @return The Matrix as a glm::mat.
                */
                glm::mat<WIDTH, HEIGHT, T> toGlm() const
                {
                    glm::mat<WIDTH, HEIGHT, T> result;
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            result[i][j] = this->_matrix[i][j];
                        }
                    }
                    return result;
                }

                /**
                 * @brief Returns the sum of all elements in the matrix.
                 *
                 * @param other The matrix to add to this matrix.
                 * @return The sum of all elements in the matrix.
                */
                Matrix<WIDTH, HEIGHT, T> operator+(const Matrix<WIDTH, HEIGHT, T>& other) const
                {
                    Matrix<WIDTH, HEIGHT, T> result;
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            result._matrix[i][j] = this->_matrix[i][j] + other._matrix[i][j];
                        }
                    }
                    return result;
                }

                /**
                 * @brief Adds the specified matrix to this matrix.
                 *
                 * @param other The matrix to add to this matrix.
                */
                void operator+=(const Matrix<WIDTH, HEIGHT, T>& other)
                {
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            this->_matrix[i][j] += other._matrix[i][j];
                        }
                    }
                }


                /**
                 * @brief Returns the difference of all elements in the matrix.
                 *
                 * @param other The matrix to subtract from this matrix.
                 * @return The difference of all elements in the matrix.
                */
                Matrix<WIDTH, HEIGHT, T> operator-(const Matrix<WIDTH, HEIGHT, T>& other) const
                {
                    Matrix<WIDTH, HEIGHT, T> result;
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            result._matrix[i][j] = this->_matrix[i][j] - other._matrix[i][j];
                        }
                    }
                    return result;
                }

                /**
                 * @brief Returns a matrix with all elements negated.
                 *
                 * @return A matrix with all elements negated.
                */
                Matrix<WIDTH, HEIGHT, T> operator-() const
                {
                    Matrix<WIDTH, HEIGHT, T> result;
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            result._matrix[i][j] = -this->_matrix[i][j];
                        }
                    }
                    return result;
                }

                /**
                 * @brief Subtracts the specified matrix from this matrix.
                 *
                 * @param other The matrix to subtract from this matrix.
                */
                void operator-=(const Matrix<WIDTH, HEIGHT, T>& other)
                {
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            this->_matrix[i][j] -= other._matrix[i][j];
                        }
                    }
                }

                /**
                 * @brief Returns the product of all elements in the matrix.
                 *
                 * @param other The matrix to multiply with this matrix.
                 * @return The product of all elements in the matrix.
                */
                Matrix<WIDTH, HEIGHT, T> operator*(const Matrix<WIDTH, HEIGHT, T>& other) const
                {
                    Matrix<WIDTH, HEIGHT, T> result;
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            result._matrix[i][j] = 0;
                            for (int k = 0; k < WIDTH; k++) {
                                result._matrix[i][j] += this->_matrix[i][k] * other._matrix[k][j];
                            }
                        }
                    }
                    return result;
                }

                /**
                 * @brief Multiplies the specified matrix with this matrix.
                 *
                 * @param other The matrix to multiply with this matrix.
                */
                void operator*=(const Matrix<WIDTH, HEIGHT, T>& other)
                {
                    *this = *this * other;
                }

                /**
                 * @brief Returns the product of all elements in the matrix.
                 *
                 * @param scalar The scalar to multiply with this matrix.
                 * @return The product of all elements in the matrix.
                */
                Matrix<WIDTH, HEIGHT, T> operator*(double scalar) const
                {
                    Matrix<WIDTH, HEIGHT, T> result;
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            result._matrix[i][j] = this->_matrix[i][j] * scalar;
                        }
                    }
                    return result;
                }

                /**
                 * @brief Multiplies the specified scalar with this matrix.
                 *
                 * @param scalar The scalar to multiply with this matrix.
                */
                void operator*=(double scalar)
                {
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            this->_matrix[i][j] *= scalar;
                        }
                    }
                }

                /**
                 * @brief Returns the quotient of all elements in the matrix.
                 *
                 * @param scalar The scalar to divide with this matrix.
                 * @return The quotient of all elements in the matrix.
                */
                Matrix<WIDTH, HEIGHT, T> operator/(double scalar) const
                {
                    if (scalar == 0) {
                        throw MatrixError("Cannot divide by zero.");
                    }
                    Matrix<WIDTH, HEIGHT, T> result;
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            result._matrix[i][j] = this->_matrix[i][j] / scalar;
                        }
                    }
                    return result;
                }

                /**
                 * @brief Divides the specified scalar with this matrix.
                 *
                 * @param scalar The scalar to divide with this matrix.
                */
                void operator/=(double scalar)
                {
                    if (scalar == 0) {
                        throw MatrixError("Cannot divide by zero.");
                    }
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            this->_matrix[i][j] /= scalar;
                        }
                    }
                }

                /**
                 * @brief Checks if the matrix is equal to the specified matrix.
                 *
                 * The function checks if the matrix is equal to the specified matrix.
                 * @param other The matrix to compare with.
                 * @return True if the matrix is equal to the specified matrix, false otherwise.
                */
                bool operator==(const Matrix<WIDTH, HEIGHT, T>& other) const
                {
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            if (this->_matrix[i][j] != other._matrix[i][j]) {
                                return false;
                            }
                        }
                    }
                    return true;
                }

                /**
                 * @brief Checks if the matrix is not equal to the specified matrix.
                 *
                 * The function checks if the matrix is not equal to the specified matrix.
                 * @param other The matrix to compare with.
                 * @return True if the matrix is not equal to the specified matrix, false otherwise.
                */
                bool operator!=(const Matrix<WIDTH, HEIGHT, T>& other) const
                {
                    return !(*this == other);
                }

                /**
                 * @brief Returns the element at the specified position.
                 *
                 * The function returns the element at the specified position.
                 * @param pos The position of the element.
                 * @return The element at the specified position.
                 * @throw MatrixError if the position is out of bounds.
                */
                std::array<T, WIDTH> operator[](int pos) const
                {
                    if (pos < 0 || pos >= HEIGHT) {
                        throw MatrixError("Position out of range");
                    }
                    return _matrix[pos];
                }

                /**
                 * @brief Returns the element at the specified position.
                 *
                 * The function returns the element at the specified position.
                 * @param pos The position of the element.
                 * @return The element at the specified position.
                 * @throw MatrixError if the position is out of bounds.
                */
                std::array<T, WIDTH>& operator[](int pos)
                {
                    if (pos < 0 || pos >= HEIGHT) {
                        throw MatrixError("Position out of range");
                    }
                    return _matrix[pos];
                }

                static Matrix<WIDTH, HEIGHT, T> identity()
                {
                    Matrix<WIDTH, HEIGHT, T> result;
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            result._matrix[i][j] = i == j ? 1 : 0;
                        }
                    }
                    return result;
                }
            private:
                std::array<std::array<T, WIDTH>, HEIGHT> _matrix;      ///< The matrix.
        };
}

/**
 * @brief Outputs the matrix to the specified output stream.
 *
 * The function outputs the matrix to the specified output stream.
 * @param os The output stream.
 * @param matrix The matrix to output.
 * @return The output stream.
*/
template<int WIDTH, int HEIGHT, typename T>
std::ostream& operator<<(std::ostream& os, const LE::Matrix<WIDTH, HEIGHT, T>& matrix)
{
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            os << matrix[i][j];
            if (j < WIDTH - 1) {
                os << " ";
            }
        }
        if (i < HEIGHT - 1) {
            os << std::endl;
        }
    }
    return os;
}
