/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Device
*/

#include "Sound/Device.hpp"

extern "C" size_t encapsulatedStrLen(const char *str)
{
    return strlen(str);
}

extern "C" LE::Sound::Device::ErrorType InitOpenALDevice(LE::Sound::Device *myDevice, const char *deviceName = NULL)
{
    ALCdevice *hardwareDevice = alcOpenDevice(deviceName);
    ALCcontext *context = NULL;

    if (!hardwareDevice)
        return LE::Sound::Device::ErrorType::CAN_NOT_OPEN_DEVICE;
    context = alcCreateContext(hardwareDevice, NULL);
    if (!context)
        return LE::Sound::Device::ErrorType::CAN_NOT_CREATE_CONTEXT;
    if (!alcMakeContextCurrent(context))
        return LE::Sound::Device::ErrorType::CAN_NOT_MAKE_CONTEXT_CURRENT;
    myDevice->setOpenALDevice(hardwareDevice);
    myDevice->setOpenALContext(context);
    return LE::Sound::Device::ErrorType::NO_ERROR;
}

extern "C" void CloseOpenALDevice(LE::Sound::Device *myDevice)
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(myDevice->getOpenALContext());
    alcCloseDevice(myDevice->getOpenALMainDevice());
}

LE::Sound::Device::Device()
{
    switch (InitOpenALDevice(this)) {
        case LE::Sound::Device::ErrorType::CAN_NOT_OPEN_DEVICE:
            throw LE::Sound::Device::SoundDeviceError("Can not open device (default)");
            break;
        case LE::Sound::Device::ErrorType::CAN_NOT_CREATE_CONTEXT:
            throw LE::Sound::Device::SoundDeviceError("Can not create context");
            break;
        case LE::Sound::Device::ErrorType::CAN_NOT_MAKE_CONTEXT_CURRENT:
            throw LE::Sound::Device::SoundDeviceError("Can not make context current");
            break;
        default:
            break;
    }
    refreshDevices();
}

LE::Sound::Device::~Device()
{
    CloseOpenALDevice(this);
}

ALCdevice *LE::Sound::Device::getOpenALMainDevice()
{
    return this->_openALMainDevice;
}

void LE::Sound::Device::setOpenALDevice(ALCdevice *openALDevice)
{
    this->_openALMainDevice = openALDevice;
}

ALCcontext *LE::Sound::Device::getOpenALContext()
{
    return this->_openALMainContext;
}

void LE::Sound::Device::setOpenALContext(ALCcontext *openALContext)
{
    this->_openALMainContext = openALContext;
}

void LE::Sound::Device::refreshDevices()
{
    this->_devices.clear();

    const ALCchar *deviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

    if (!deviceList)
        return;
    while (encapsulatedStrLen(deviceList) > 0) {
        this->_devices.push_back(deviceList);
        deviceList += encapsulatedStrLen(deviceList) + 1;
    }
}

std::vector<std::string> LE::Sound::Device::getDevices()
{
    return this->_devices;
}
