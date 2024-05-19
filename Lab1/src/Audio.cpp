// REFERENCE CREDIT
// The Audio.h & Audio.cpp files were created by following Mike Shah's YouTube tutorial
// "[Ep. 35] Simple SDL Audio API tutorial(Not using SDL Mixer) | Introduction to SDL2"
// Available at: https://www.youtube.com/watch?v=hZ0TGCUcY2g&t=767s
// Accessed 18th & 19th May 2024
//
// Class, Method, & Variable names have been changed where possible but are generally similar
// as this is a new area for me and these names made the most sense with the limited knowledge I have
//

#include "Audio.h"

Audio::Audio(const std::string& fileName)
{
	if (SDL_LoadWAV(fileName.c_str(), &m_audioSpec, &m_wavStart, &m_wavLength) == nullptr)
	{
		std::cerr << "Sound loading error: " << SDL_GetError() << std::endl;
	}
}

Audio::~Audio()
{
	SDL_FreeWAV(m_wavStart);
	SDL_CloseAudioDevice(m_audioDevice);
}

void Audio::PlayAudio()
{
	int status = SDL_QueueAudio(m_audioDevice, m_wavStart, m_wavLength);
	SDL_PauseAudioDevice(m_audioDevice, 0);
}

void Audio::SetUpDevice()
{
	m_audioDevice = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
	
	if (0 == m_audioDevice)
	{
		std::cerr << "Audio device error: " << SDL_GetError() << std::endl;
	}
}