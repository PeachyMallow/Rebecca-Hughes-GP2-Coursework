#pragma once

#include <SDL/SDL.h>

#include <iostream>

class Audio
{
	// device audio will play on - headphones, speakers etc
	SDL_AudioDeviceID m_audioDevice;

	//wav file properties
	SDL_AudioSpec m_audioSpec;
	Uint8* m_wavStart;
	Uint32 m_wavLength;
	
public:
	Audio();
	~Audio();

	void LoadAudio(const std::string& fileName);
	void PlayAudio();
	void StopAudio();
	void SetUpDevice();

};

