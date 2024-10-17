/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Device
*/

#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <string.h>

#include <vector>
#include <string>

#include "Error.hpp"

namespace LE {
    namespace Sound {
        /**
         * @class Device
         * @brief Represents an audio device and its associated context.
         *
         * The Device class provides functionality to manage an audio device and its associated context
         * using the OpenAL library. It allows opening and closing the device, creating and setting the
         * context, refreshing the available devices, and retrieving the list of available devices.
         */
        class Device {
            public:
                /**
                 * @brief The ErrorType enum represents the possible error types.
                 */
                enum ErrorType {
                    NO_ERROR,                   ///< No error
                    CAN_NOT_OPEN_DEVICE,        ///< Unable to open the device
                    CAN_NOT_CREATE_CONTEXT,     ///< Unable to create the context
                    CAN_NOT_MAKE_CONTEXT_CURRENT,///< Unable to make the context current
                };

                /**
                 * @brief The SoundDeviceError class represents an error related to the sound device.
                 */
                class SoundDeviceError : public Error {
                public:
                    /**
                     * @brief Constructs a SoundDeviceError object with the given error message.
                     * @param message The error message.
                     */
                    SoundDeviceError(const std::string &message) : Error(message) {}

                    /**
                     * @brief Destructor for the SoundDeviceError class.
                     */
                    ~SoundDeviceError() = default;
                };

                /**
                 * @brief Default constructor for the Device class.
                 */
                Device();

                /**
                 * @brief Destructor for the Device class.
                 */
                ~Device();

                /**
                 * @brief Refreshes the list of available sound devices.
                 */
                void refreshDevices();

                /**
                 * @brief Returns the main OpenAL device.
                 * @return A pointer to the main OpenAL device.
                 */
                ALCdevice *getOpenALMainDevice();

                /**
                 * @brief Sets the main OpenAL device.
                 * @param openALDevice A pointer to the OpenAL device to set.
                 */
                void setOpenALDevice(ALCdevice *openALDevice);

                /**
                 * @brief Returns the OpenAL context.
                 * @return A pointer to the OpenAL context.
                 */
                ALCcontext *getOpenALContext();

                /**
                 * @brief Sets the OpenAL context.
                 * @param openALContext A pointer to the OpenAL context to set.
                 */
                void setOpenALContext(ALCcontext *openALContext);

                /**
                 * @brief Returns a vector of available sound devices.
                 * @return A vector of strings representing the available sound devices.
                 */
                std::vector<std::string> getDevices();

            protected:
                ALCdevice *_openALMainDevice;            ///< The main OpenAL device
                ALCcontext *_openALMainContext;          ///< The OpenAL context
                std::vector<std::string> _devices;       ///< Vector of available sound devices
        };
    }
}
