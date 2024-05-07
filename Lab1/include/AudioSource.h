//#pragma once
//
//#include <AL/al.h>
//#include <AL/alc.h>
//#include <iostream>
//
//// generates sources
//class AudioSource
//{
//	//Int soundID
//	int sourceID;
//
//	//Constructor
//	AudioSource() : sourceID(0)
//	{
//		//	sourceID = AL10.alGenSources()
//		//sourceID = 
//		
//			//	AL10.alSourcef(sourceID, AL10.AL_GAIN, 1) <- Volume
//			//	AL10.alSourcef(sourceID, AL10.AL_PITCH, 1)
//			//	AL10.alSource3f(sourceID, AL10.AL_POSITION, 0, 0, 0) 0, 0, 0 value of the property
//	}
//
//	//Destructor
//	~AudioSource()
//	{
//		//	AL10.alDeleteSources(sourceID)
//	}
//	
//
//	//Play(int buffer)
//	void Play(int buffer) {
//		//	AL10.alSourcei(sourceID, AL10.AL_Buffer, buffer) <- associate buffer with source
//		//	AL10.alSourcePlay(sourceID)
//	}
//
//};