#include "Audio.h"

// stopped video at 12:47
Audio::Audio()
{

}

Audio::~Audio()
{
	SDL_FreeWAV(m_wavStart);
	SDL_CloseAudioDevice(m_audioDevice);
}

void Audio::LoadAudio(const std::string& fileName)
{
	if (SDL_LoadWAV(fileName.c_str(), &m_audioSpec, &m_wavStart, &m_wavLength) == nullptr)
	{
		std::cerr << "Sound loading error: " << SDL_GetError() << std::endl;
	}
}

void Audio::PlayAudio()
{
	int status = SDL_QueueAudio(m_audioDevice, m_wavStart, m_wavLength);
	SDL_PauseAudioDevice(m_audioDevice, 0);
}

void Audio::StopAudio()
{
	SDL_PauseAudioDevice(m_audioDevice, 1);
}
