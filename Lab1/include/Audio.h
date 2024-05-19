// REFERENCE CREDIT
// The Audio.h & Audio.cpp files were created by following Mike Shah's YouTube tutorial
// "[Ep. 35] Simple SDL Audio API tutorial(Not using SDL Mixer) | Introduction to SDL2"
// Available at: https://www.youtube.com/watch?v=hZ0TGCUcY2g&t=767s
// Accessed 18th & 19th May 2024
//
// Class, Method, & Variable names have been changed where possible but are generally similar
// as this is a new area for me and these names made the most sense with the limited knowledge I have
//

#pragma once

#include <SDL/SDL.h>

#include <iostream>

class Audio
{
	// device audio will play on - headphones, speakers etc
	SDL_AudioDeviceID m_audioDevice;

	// wav file properties
	SDL_AudioSpec m_audioSpec;
	Uint8* m_wavStart;
	Uint32 m_wavLength;
	
public:
	Audio(const std::string& fileName);
	~Audio();

	void PlayAudio(/*const bool loop*/);
	void StopAudio();
	void SetUpDevice();
	SDL_AudioDeviceID GetAudioDevice() { return this->m_audioDevice; }
	Uint32 GetAudioLength() { return this->m_wavLength; };
};