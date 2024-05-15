#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>
#include <vector>

#include "Camera.h"
#include "Display.h" 
#include "Mesh.h"
#include "Shader.h"
#include "stb_image.h" //needed?
#include "Texture.h"
#include "Transform.h"

enum class GameState{ PLAY, EXIT };

enum GameObjects : int { FROG, BEE, PUMPKIN, NUM_OBJECTS };

enum Shaders : int { FOG, BASIC, TOON, NUM_SHADERS };

class MainGame
{
	void InitSystems();
	void ProcessInput();
	void GameLoop();
	void DrawGame();

	void SetTransforms(int objectType);
	void SetShader(int shaderType);
	void SetTexture();

	bool Collided(glm::vec3 pos1, float radius1, glm::vec3 pos2, float radius2);

	Display _gameDisplay/*(1024, 768, const "Labs")*/;
	GameState _gameState;

	int mouseX, mouseY;

	Mesh m_mesh[NUM_OBJECTS]; // make a vector?
	/*Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;*/
	Camera m_Camera;

	Texture texture[NUM_OBJECTS];
	/*Texture texture2;
	Texture texture3;*/

	Shader m_shader[NUM_SHADERS];
	/*Shader basicShader;
	Shader toonShader;
	Shader fogShader;*/


	float counter;

public:
	MainGame() /*: _gameDisplay(1024, 768, "Game Window"), _gameState(GameState::PLAY), counter(0)*/;
	~MainGame();

	void Run();
};