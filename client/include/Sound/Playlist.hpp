/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Playlist
*/

#pragma once

#include "Sound/Sound.hpp"

#include "Error.hpp"

#include <string>
#include <vector>

class Utils;

namespace LE {
    namespace Sound {
        /**
         * @class Playlist
         * @brief Represents a playlist of music tracks.
         *
         * The Playlist class allows you to manage a collection of music tracks and perform operations such as playing, pausing, stopping, and navigating between tracks.
         */
        class Playlist {
            public:
                /**
                 * @brief Constructs a Playlist object with the specified path.
                 *
                 * @param path The path to the playlist file.
                 */
                Playlist(const std::string &path);

                /**
                 * @brief Destroys the Playlist object.
                 */
                ~Playlist();

                /**
                 * @brief Plays the current music track.
                 */
                void play();

                /**
                 * @brief Pauses the currently playing music track.
                 */
                void pause();

                /**
                * @brief Plays or pauses the currently playing music track, depending on its current state.
                */
                void playPause();

                /**
                 * @brief Stops the currently playing music track.
                 */
                void stop();

                /**
                 * @brief Skips to the next music track in the playlist.
                 */
                void next();

                /**
                 * @brief Skips to the previous music track in the playlist.
                 */
                void previous();

            protected:
                std::vector<LE::Sound::Sound *> _musics; ///< The collection of music tracks in the playlist.
                size_t _currentMusic; ///< The index of the currently playing music track.
                bool _isPlaying; ///< A flag indicating whether the playlist is currently playing.
        };
    }
}
