#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>
#include <vector>

#include "Camera.h"
#include "Display.h" 
#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"
#include "stb_image.h" //needed?
#include "Texture.h"
#include "Transform.h"

enum class GameState{ PLAY, EXIT };

enum GameObjects : int { FROG, BEE, PUMPKIN, NUM_GAME_OBJECTS };

enum Shaders : int { FOG, BASIC, TOON, RIM_L, NUM_SHADERS };

//float counter;
//Transform transform[3];

class MainGame
{
	// creates GameObjects. loading: models, textures, & setting initial transforms
	void LoadAndSetSystems();
	void ProcessInput();
	void GameLoop();
	void DrawGame();

	//void SetTransforms(int objectType);
	void SetShader(const std::string& shaderName);
	//void SetTexture();

	bool Collided(glm::vec3 pos1, float radius1, glm::vec3 pos2, float radius2);

	Display m_gameDisplay/*(1024, 768, const "Labs")*/;
	glm::vec4 m_sceneBGColour = { 0.11f, 0.07f, 0.033f, 1.0f }; // dark brown
	Camera m_Camera;
	GameState _gameState;

	int mouseX, mouseY;

	std::vector<GameObject> m_gameObjects;
	std::unordered_map<std::string, Shader> m_shaders;


	//Shader m_shader[NUM_SHADERS];
	std::string currentShader = "Basic";

	SDL_Event evnt;
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	//Mesh m_mesh[NUM_OBJECTS]; // make a vector?
	//Texture texture[NUM_OBJECTS];

public:
	MainGame() /*: _gameDisplay(1024, 768, "Game Window"), _gameState(GameState::PLAY), counter(0)*/;
	~MainGame();

	void Run();

	GLfloat m_frameCounter;
};