/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Playlist
*/

#include "Sound/Playlist.hpp"

LE::Sound::Playlist::Playlist(const std::string &path)
{
    std::vector<std::string> mp3Files = Utils::getDirectoryFiles(path, ".mp3");

    for (const auto &file : mp3Files) {
        this->_musics.push_back(new LE::Sound::Sound(file, LE::Sound::Sound::FileType::MP3));
    }

    std::vector<std::string> wavFiles = Utils::getDirectoryFiles(path, ".wav");

    for (const auto &file : wavFiles) {
        this->_musics.push_back(new LE::Sound::Sound(file, LE::Sound::Sound::FileType::WAV));
    }

    this->_currentMusic = 0;
    this->_isPlaying = false;
}

LE::Sound::Playlist::~Playlist()
{
}

void LE::Sound::Playlist::play()
{
    this->_musics[this->_currentMusic]->play();
    this->_isPlaying = true;
}

void LE::Sound::Playlist::pause()
{
    this->_musics[this->_currentMusic]->pause();
    this->_isPlaying = false;
}

void LE::Sound::Playlist::playPause()
{
    if (this->_isPlaying)
        this->pause();
    else
        this->play();
}

void LE::Sound::Playlist::stop()
{
    this->_musics[this->_currentMusic]->stop();
    this->_isPlaying = false;
    this->_currentMusic = 0;
}

void LE::Sound::Playlist::next()
{
    this->_musics[this->_currentMusic]->stop();
    this->_currentMusic++;
    if (this->_currentMusic >= this->_musics.size())
        this->_currentMusic = 0;
    this->_musics[this->_currentMusic]->play();
}

void LE::Sound::Playlist::previous()
{
    this->_musics[this->_currentMusic]->stop();
    this->_currentMusic = this->_currentMusic == 0 ? this->_musics.size() - 1 : this->_currentMusic - 1;
    this->_musics[this->_currentMusic]->play();
}
