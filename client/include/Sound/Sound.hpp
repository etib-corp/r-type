/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Sound
*/

#pragma once

#include "Sound/dr_mp3.h"
#include "Sound/dr_wav.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <string>
#include <vector>
#include <thread>

#include "Error.hpp"

namespace LE {
    namespace Sound {
        /**
         * @brief The Sound class represents a sound object that can be played, paused, stopped, and replayed.
         */
        class Sound {
            public:
                /**
                 * @brief The SoundError class represents an error that can occur during sound operations.
                 */
                class SoundError : public LE::Error {
                public:
                    /**
                     * @brief Constructs a SoundError object with the given error message.
                     * @param message The error message.
                     */
                    SoundError(const std::string &message) : Error(message) {}

                    /**
                     * @brief Destructor for the SoundError class.
                     */
                    ~SoundError() = default;
                };

                /**
                 * @brief The FileType enum represents the type of sound file.
                 */
                enum FileType {
                    WAV,     /**< WAV file type */
                    MP3,     /**< MP3 file type */
                    UNKNOWN  /**< Unknown file type */
                };

                /**
                 * @brief Constructs a Sound object with the specified file path and type.
                 * @param path The path to the sound file.
                 * @param type The type of the sound file.
                 */
                Sound(const std::string &path, FileType type = FileType::MP3);

                /**
                 * @brief Destructor for the Sound class.
                 */
                ~Sound();

                /**
                 * @brief Plays the sound.
                 */
                void play();

                /**
                 * @brief Pauses the sound.
                 */
                void pause();

                /**
                 * @brief Stops the sound.
                 */
                void stop();

                /**
                 * @brief Restarts the sound from the beginning.
                 */
                void replay();

            protected:
                ALuint _buffer;        /**< OpenAL buffer ID */
                ALuint _source;        /**< OpenAL source ID */
                FileType _type;        /**< Type of the sound file */
                drwav _wav;            /**< WAV file object */
                drmp3 _mp3;            /**< MP3 file object */
                std::string _path;     /**< Path to the sound file */
                std::thread _stream;   /**< Thread for streaming sound data */
        };
    }
}
