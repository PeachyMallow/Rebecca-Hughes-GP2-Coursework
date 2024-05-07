//#pragma once
//
//#include <AL/al.h>
//#include <AL/alc.h>
//#include "Audio.h"
//#include <iostream>
//#include <vector>
//
//// buffers
//// listener
////loads files
//
//class AudioMaster
//{
//	//List of buffers
//	std::vector<int> buffers; // might need push_back somewhere
//
//public:
//
//	AudioMaster() {};
//	~AudioMaster() {
//	
//	} //Destructor AL.destroy()	//Loop to cycle through buffer list – AL10.alDeleteBuffers(buffer)
//
//	//Initialize with AL.create()
//	void InitAudioBuffers() {
//		
//		// initialise the OpenAL Device
//		ALCdevice* openALDevice = alcOpenDevice(nullptr); // nullptr says open the default device but can specify from device list if wanted
//		if (!openALDevice)
//		{
//			/* fail */
//		}
//
//		// create audio context
//		ALCcontext* openALContext;
//		if (!alcCall(alcCreateContext, openALContext, openALDevice, openALDevice, nullptr) || !openALContext)
//		{
//			std::cerr << "ERROR: Could not create audio context" << std::endl;
//			/* probably exit program */
//		}
//
//		// make context current
//		// Making the context current is needed to do any further operating on the context (or sources or listeners within it). 
//		// It’s either going to return true or false, the only possible error value reported by alcGetError is ALC_INVALID_CONTEXT 
//		// which is fairly self-explanatory
//		ALCboolean contextMadeCurrent = false;
//		if (!alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, openALContext)
//			|| contextMadeCurrent != ALC_TRUE)
//		{
//			std::cerr << "ERROR: Could not make audio context current" << std::endl;
//			/* probably exit or give up on having sound */
//		}
//
//		//contextMadeCurrent maybe make variable external to this method
//		if (!alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr))
//		{
//			/* what can you do? */
//		}
//
//		if (!alcCall(alcDestroyContext, openALDevice, openALContext))
//		{
//			/* not much you can do */
//		}
//
//
//	};
//
//	//Int loadSound(String filename)
//	int LoadAudioFile(std::string fileName)
//	{
//		//int buffer – AL10.GenBuffers() add this to list
//		
//		//some method from dr_libs to load sound(with filename)
//		//Store sound data into the buffer by calling AL10.alBufferData(buffer, format of data, audio data, sample rate) last three might be in dr_libs
//		//Then dispose of wave file
//		//Return buffer ID
//	}
//
//
//
//	//SetListenerData / Properties
//	//AL10.alListener3f(AL10.AL_POSITION, 0, 0, 0)
//	//AL10.alListener3f(AL10.AL_VELOCITY, 0, 0, 0)
//
//
//};