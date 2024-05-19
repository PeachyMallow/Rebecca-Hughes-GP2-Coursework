#pragma once

//#include <SDL\SDL.h>
//#include <GL\glew.h>
//#include <vector>

#include "Audio.h"
#include "Camera.h"
#include "DisplayWindow.h" 
#include "GameObject.h"
//#include "Mesh.h"
#include "ShaderManager.h"
//#include "stb_image.h" //needed?
//#include "Texture.h"
//#include "Transform.h"

enum class GameState{ PLAY, EXIT };

enum GameObjects : int { FROG, BEE, PUMPKIN, NUM_GAME_OBJECTS };

//enum Shaders : int { FOG, BASIC, TOON, RIM_L, NUM_SHADERS };

//float counter;

class GameManager
{
	// creates GameObjects. loading: models, textures, & setting initial transforms
	void LoadAndSetSystems();
	void ProcessInput();
	void GameLoop();
	void DrawGame();

	//void SetTransforms(int objectType);
	// binds shader to parameter passed
	void SetShader(const std::string& shaderName);

	void AudioStatus();
	bool Collided(const glm::vec3 pos1, const float radius1, const glm::vec3 pos2, const float radius2);

	DisplayWindow m_gameDisplay;
	Camera m_camera;
	GameState m_gameState;

	int mouseX, mouseY;

	std::vector<GameObject> m_gameObjects;
	std::unordered_map<std::string, ShaderManager> m_shaders;

	std::string currentShader = "Basic";
	
	Audio* m_backgroundAudio;
	Audio* m_collisionAudio;
	SDL_AudioDeviceID m_BGAudioDev;

	SDL_Event m_evnt;
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	//Mesh m_mesh[NUM_OBJECTS]; // make a vector?
	//Texture texture[NUM_OBJECTS];

public:
	GameManager();
	~GameManager() {};

	void RunGame();

	GLfloat m_frameCounter;
};