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

void Audio::PlayAudio(/*const bool loop*/)
{
	int status = SDL_QueueAudio(m_audioDevice, m_wavStart, m_wavLength);



	SDL_PauseAudioDevice(m_audioDevice, 0);

	/*switch (SDL_GetAudioDeviceStatus(m_audioDevice))
	{
	case SDL_AUDIO_STOPPED: std::cout << ("stopped\n") << std::endl; break;
	case SDL_AUDIO_PLAYING: std::cout << ("playing\n") << std::endl; break;
	case SDL_AUDIO_PAUSED: std::cout << ("paused\n") << std::endl; break;
	default: std::cout << ("???") << std::endl; break;
	}*/

	/*std::cout << m_wavLength << std::endl;*/
}

void Audio::StopAudio()
{
	SDL_PauseAudioDevice(m_audioDevice, 1);
}

void Audio::SetUpDevice()
{
	m_audioDevice = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
	
	if (0 == m_audioDevice)
	{
		std::cerr << "Audio device error: " << SDL_GetError() << std::endl;
	}
}