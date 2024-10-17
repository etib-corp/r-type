/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Sound
*/

#define DR_MP3_IMPLEMENTATION
#define DR_WAV_IMPLEMENTATION

#include "Sound/Sound.hpp"

LE::Sound::Sound::Sound(const std::string &path, FileType type)
{
    std::vector<int16_t> samples;
    size_t totalPCMFrameCount = 0;
    ALenum format;

    this->_path = path;
    this->_type = type;
    switch (type) {
        case FileType::WAV:
            if (!drwav_init_file(&this->_wav, path.c_str(), NULL))
                throw SoundError("Can not open wav file : [" + path + "]");
            samples = std::vector<int16_t>(this->_wav.totalPCMFrameCount * this->_wav.channels);
            drwav_read_pcm_frames_s16(&this->_wav, this->_wav.totalPCMFrameCount, samples.data());
            drwav_uninit(&this->_wav);
            if (this->_wav.channels == 1)
                format = AL_FORMAT_MONO16;
            else if (this->_wav.channels == 2)
                format = AL_FORMAT_STEREO16;
            else
                throw SoundError("Invalid channel count : [" + path + "]");
            alGenBuffers(1, &this->_buffer);
            alBufferData(this->_buffer, format, samples.data(), samples.size() * sizeof(int16_t), this->_wav.sampleRate);
            break;
        case FileType::MP3:
            if (!drmp3_init_file(&this->_mp3, path.c_str(), NULL))
                throw SoundError("Can not open mp3 file : [" + path + "]");
            samples.reserve(4096);
            int16_t tempBuffer[4096];
            size_t framesRead;
            while ((framesRead = drmp3_read_pcm_frames_s16(&this->_mp3, 4096 / this->_mp3.channels, tempBuffer)) > 0) {
                samples.insert(samples.end(), tempBuffer, tempBuffer + framesRead * this->_mp3.channels);
                totalPCMFrameCount += framesRead;
            }
            drmp3_read_pcm_frames_s16(&this->_mp3, totalPCMFrameCount, samples.data());
            drmp3_uninit(&this->_mp3);
            if (this->_mp3.channels == 1)
                format = AL_FORMAT_MONO16;
            else if (this->_mp3.channels == 2)
                format = AL_FORMAT_STEREO16;
            else
                throw SoundError("Invalid channel count : [" + path + "]");
            alGenBuffers(1, &this->_buffer);
            alBufferData(this->_buffer, format, samples.data(), samples.size() * sizeof(int16_t), this->_mp3.sampleRate);
            break;
        default:
            throw SoundError("Unknown file type : [" + path + "]");
            break;
    }
    alGenSources(1, &this->_source);
    alSourcei(this->_source, AL_BUFFER, this->_buffer);
}

LE::Sound::Sound::~Sound()
{
    alDeleteSources(1, &this->_source);
    alDeleteBuffers(1, &this->_buffer);
}

void LE::Sound::Sound::play()
{

    alSourcePlay(this->_source);
    this->_stream = std::thread([this] {
        ALint state;

        alGetSourcei(this->_source, AL_SOURCE_STATE, &state);
        while (state == AL_PLAYING) {
            alGetSourcei(this->_source, AL_SOURCE_STATE, &state);
        }
    });
    this->_stream.detach();
}

void LE::Sound::Sound::pause()
{
    alSourcePause(this->_source);
}

void LE::Sound::Sound::stop()
{
    alSourceStop(this->_source);
}

void LE::Sound::Sound::replay()
{
    alSourceRewind(this->_source);
    this->play();
}
