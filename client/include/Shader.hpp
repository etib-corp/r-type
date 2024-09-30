/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Shader
*/

#pragma once

// Engine include
#include "Error.hpp"
#include "Maths/Matrix.hpp"
#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Vector4.hpp"

#include "glm.hpp"

#include "Window.hpp"

// C++ include
#include <fstream>
#include <sstream>
#include <string>

namespace LE {
    /**
     * @class Shader
     * @brief The Shader class is responsible for managing OpenGL shaders.
     *
     * The Shader class provides functionalities for compiling and using OpenGL shaders.
     *
     * @note All shaders files are stored in `client/assets/shaders/`.
     */
    class Shader {
        public:
            /**
             * @brief The ShaderError class represents an error that can occur during shader compilation.
            */
            class ShaderError : public Error {
                public:
                    /**
                     * @brief Constructs a ShaderError object with the given error message.
                     * @param message The error message.
                    */
                    ShaderError(const std::string &message) : Error(message) {}
            };

            /**
             * @brief Construct a new Shader object
             * This constructor will create a default shader and then call the compile method.
             *
             * @throw ShaderError if the shader compilation or linking failed.
             */
            Shader();

            /**
             * @brief Construct a new Shader object
             * This constructor will call the compile method with the content of the files.
             *
             * @param vertexPath Path to the vertex shader file
             * @param fragmentPath Path to the fragment shader file
             * @throw ShaderError if the shader compilation or linking failed.
            */
            Shader(const std::string &vertexPath, const std::string &fragmentPath);
            ~Shader();


            /**
             * @brief Use the shader
             * This method will call glUseProgram with the shader ID.
             *
             * @note This method should be called before drawing anything.
            */
            void use();

            /**
             * @brief Get the ID of the shader
             *
             * @return unsigned int The ID of the shader
            */
            unsigned int getID() const;

            /**
             * @brief Set a bool uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            void setBool(const std::string &name, bool value) const;

            /**
             * @brief Set a double uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            void setDouble(const std::string &name, double value) const;

            /**
             * @brief Set a float uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            void setFloat(const std::string &name, float value) const;

            /**
             * @brief Set a signed int uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            void setInt(const std::string &name, int value) const;

            /**
             * @brief Set a vec2 uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            template<typename T>
            void setVec2(const std::string &name, const LE::Vector2<T> &value) const;

            /**
             * @brief Set a vec3 uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            template<typename T>
            void setVec3(const std::string &name, const LE::Vector3<T> &value) const;

            /**
             * @brief Set a vec4 uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            template<typename T>
            void setVec4(const std::string &name, const LE::Vector4<T> &value) const;

            /**
             * @brief Set a mat uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
             * @tparam DIMENSION The dimension of the matrix
             * @note The matrix must be square
             */
            template <int DIMENSION>
            void setMat(const std::string &name, const LE::Matrix<DIMENSION, DIMENSION, float> &value) const
            {
                unsigned int location = glGetUniformLocation(this->_ID, name.c_str());
                float *values = value.value_ptr();

                if (location == -1)
                    throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + "\n");
                switch (DIMENSION) {
                    case 2:
                        glUniformMatrix2fv(location, 1, GL_FALSE, values);
                        break;
                    case 3:
                        glUniformMatrix3fv(location, 1, GL_FALSE, values);
                        break;
                    case 4:
                        glUniformMatrix4fv(location, 1, GL_FALSE, values);
                        break;
                    default:
                        throw ShaderError("ERROR\n\tINVALID MATRIX DIMENSION\n\t\twhile trying to set " + name + "\n");
                }
            }

            /**
             * @brief Compile the shader
             *
             * @param vertexSource The source code of the vertex shader
             * @param fragmentSource The source code of the fragment shader
             * @throw ShaderError if the shader compilation or linking failed.
            */
            void compile(const std::string &vertexSource, const std::string &fragmentSource);

        private:
            GLuint _ID;           ///< The ID of the shader program
            GLuint _vertex;       ///< The ID of the vertex shader
            GLuint _fragment;     ///< The ID of the fragment shader
    };
}
