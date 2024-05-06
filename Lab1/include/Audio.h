#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

// copied from https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/


#define alCall(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_OPT__)

bool check_al_errors(const std::string& filename, const std::uint_fast32_t line)
{
    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
    {
        std::cerr << "***ERROR*** (" << filename << ": " << line << ")\n";
        switch (error)
        {
        case AL_INVALID_NAME:
            std::cerr << "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function";
            break;
        case AL_INVALID_ENUM:
            std::cerr << "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function";
            break;
        case AL_INVALID_VALUE:
            std::cerr << "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function";
            break;
        case AL_INVALID_OPERATION:
            std::cerr << "AL_INVALID_OPERATION: the requested operation is not valid";
            break;
        case AL_OUT_OF_MEMORY:
            std::cerr << "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory";
            break;
        default:
            std::cerr << "UNKNOWN AL ERROR: " << error;
        }
        std::cerr << std::endl;
        return false;
    }
    return true;
}

template<typename alFunction, typename... Params>
auto alCallImpl(const char* filename,
    const std::uint_fast32_t line,
    alFunction function,
    Params... params)
    -> typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, decltype(function(params...))>
{
    auto ret = function(std::forward<Params>(params)...);
    check_al_errors(filename, line);
    return ret;
}

template<typename alFunction, typename... Params>
auto alCallImpl(const char* filename,
    const std::uint_fast32_t line,
    alFunction function,
    Params... params)
    -> typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
{
    function(std::forward<Params>(params)...);
    return check_al_errors(filename, line);
}

#define alcCall(function, device, ...) alcCallImpl(__FILE__, __LINE__, function, device, __VA_OPT__)

bool check_alc_errors(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device)
{
    ALCenum error = alcGetError(device);
    if (error != ALC_NO_ERROR)
    {
        std::cerr << "***ERROR*** (" << filename << ": " << line << ")\n";
        switch (error)
        {
        case ALC_INVALID_VALUE:
            std::cerr << "ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function";
            break;
        case ALC_INVALID_DEVICE:
            std::cerr << "ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function";
            break;
        case ALC_INVALID_CONTEXT:
            std::cerr << "ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function";
            break;
        case ALC_INVALID_ENUM:
            std::cerr << "ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function";
            break;
        case ALC_OUT_OF_MEMORY:
            std::cerr << "ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function";
            break;
        default:
            std::cerr << "UNKNOWN ALC ERROR: " << error;
        }
        std::cerr << std::endl;
        return false;
    }
    return true;
}

template<typename alcFunction, typename... Params>
auto alcCallImpl(const char* filename,
    const std::uint_fast32_t line,
    alcFunction function,
    ALCdevice* device,
    Params... params)
    -> typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
{
    function(std::forward<Params>(params)...);
    return check_alc_errors(filename, line, device);
}

template<typename alcFunction, typename ReturnType, typename... Params>
auto alcCallImpl(const char* filename,
    const std::uint_fast32_t line,
    alcFunction function,
    ReturnType& returnValue,
    ALCdevice* device,
    Params... params)
    -> typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool>
{
    returnValue = function(std::forward<Params>(params)...);
    return check_alc_errors(filename, line, device);
}

//ALCdevice* openALDevice = alcOpenDevice(nullptr);
//if (!openALDevice)
//return 0;
//
//ALCcontext* openALContext;
//if (!alcCall(alcCreateContext, openALContext, openALDevice, openALDevice, nullptr) || !openALContext)
//{
//    std::cerr << "ERROR: Could not create audio context" << std::endl;
//    return 0;
//}
//ALCboolean contextMadeCurrent = false;
//if (!alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, openALContext)
//    || contextMadeCurrent != ALC_TRUE)
//{
//    std::cerr << "ERROR: Could not make audio context current" << std::endl;
//    return 0;
//}
//
//std::uint8_t channels;
//std::int32_t sampleRate;
//std::uint8_t bitsPerSample;
//std::vector<char> soundData;
//if (!load_wav("iamtheprotectorofthissystem.wav", channels, sampleRate, bitsPerSample, soundData))
//{
//    std::cerr << "ERROR: Could not load wav" << std::endl;
//    return 0;
//}
//
//ALuint buffer;
//alCall(alGenBuffers, 1, &buffer);
//
//ALenum format;
//if (channels == 1 && bitsPerSample == 8)
//format = AL_FORMAT_MONO8;
//else if (channels == 1 && bitsPerSample == 16)
//format = AL_FORMAT_MONO16;
//else if (channels == 2 && bitsPerSample == 8)
//format = AL_FORMAT_STEREO8;
//else if (channels == 2 && bitsPerSample == 16)
//format = AL_FORMAT_STEREO16;
//else
//{
//    std::cerr
//        << "ERROR: unrecognised wave format: "
//        << channels << " channels, "
//        << bitsPerSample << " bps" << std::endl;
//    return 0;
//}
//
//alCall(alBufferData, buffer, format, soundData.data(), soundData.size(), sampleRate);
//soundData.clear(); // erase the sound in RAM
//
//ALuint source;
//alCall(alGenSources, 1, &source);
//alCall(alSourcef, source, AL_PITCH, 1);
//alCall(alSourcef, source, AL_GAIN, 1.0f);
//alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
//alCall(alSource3f, source, AL_VELOCITY, 0, 0, 0);
//alCall(alSourcei, source, AL_LOOPING, AL_FALSE);
//alCall(alSourcei, source, AL_BUFFER, buffer);
//
//alCall(alSourcePlay, source);
//
//ALint state = AL_PLAYING;
//
//while (state == AL_PLAYING)
//{
//    alCall(alGetSourcei, source, AL_SOURCE_STATE, &state);
//}
//
//alCall(alDeleteSources, 1, &source);
//alCall(alDeleteBuffers, 1, &buffer);
//
//alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
//alcCall(alcDestroyContext, openALDevice, openALContext);
//
//ALCboolean closed;
//alcCall(alcCloseDevice, closed, openALDevice, openALDevice);
