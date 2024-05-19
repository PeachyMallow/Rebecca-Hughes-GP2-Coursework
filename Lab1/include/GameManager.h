#pragma once

#include "Audio.h"
#include "Camera.h"
#include "DisplayWindow.h" 
#include "GameObject.h"
#include "ShaderManager.h"

enum class GameState{ PLAY, EXIT };

enum GameObjects : int { FROG, BEE, PUMPKIN, NUM_GAME_OBJECTS };

class GameManager
{
	// creates GameObjects. loading: models, textures, & setting initial transforms
	void LoadAndSetSystems();
	void ProcessInput();
	void GameLoop();
	void RenderScene();

	void SetShader(const std::string& shaderName);
	bool Collided(const glm::vec3 pos1, const float radius1, const glm::vec3 pos2, const float radius2);

	// class objects
	DisplayWindow m_gameDisplay;
	Camera m_camera;
	GameState m_gameState;
	Audio* m_backgroundAudio;
	Audio* m_collisionAudio;

	// game objects
	std::vector<GameObject> m_gameObjects;
	GLuint selectedGameObj = FROG;

	// shaders
	std::unordered_map<std::string, ShaderManager> m_shaders;
	std::string currentShader = "Basic";
	
	// input
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

public:
	GameManager();
	~GameManager() {};

	void RunGame();
};