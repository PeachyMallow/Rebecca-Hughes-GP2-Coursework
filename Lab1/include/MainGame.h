#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>

#include "Camera.h"
#include "Display.h" 
#include "Mesh.h"
#include "Shader.h"
#include "stb_image.h" //needed?
#include "Texture.h"
#include "Transform.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
	void InitSystems();
	void ProcessInput();
	void GameLoop();
	void DrawGame();
	bool Collided(glm::vec3 pos1, float radius1, glm::vec3 pos2, float radius2);

	Display _gameDisplay/*(1024, 768, const "Labs")*/;
	GameState _gameState;
	Mesh mesh; // temp to get lab 4 to work
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Camera myCamera;
	Texture texture;
	Texture texture2;
	Texture texture3;
	Shader basicShader;
	Shader toonShader;
	Shader fogShader;


	float counter;

public:
	MainGame() /*: _gameDisplay(1024, 768, "Game Window"), _gameState(GameState::PLAY), counter(0)*/;
	~MainGame();

	void Run();
};