#include "GameManager.h"

GameManager::GameManager() 
	: m_gameDisplay(1024, 768, glm::vec4(0.05f, 0.04f, 0.015f, 1.0f), "Scene Window"), 
	m_camera(glm::vec3(0, 0, -10), 70.0f, (float)m_gameDisplay.GetWidth() / m_gameDisplay.GetHeight(), 0.01f, 1000.0f),
	m_gameState(GameState::PLAY)
{
	// pre-allocates correct amount of memory needed for gameObjects per the enum in header
	// to prevent reallocation of memory once objects are added
	m_gameObjects.reserve(NUM_GAME_OBJECTS);

	// set up audio
	m_backgroundAudio = new Audio("..\\res\\sounds\\background.wav");
	m_backgroundAudio->SetUpDevice();
	
	m_collisionAudio = new Audio("..\\res\\sounds\\bounce.wav");
	m_collisionAudio->SetUpDevice();
}

void GameManager::RunGame()
{
	this->LoadAndSetSystems();
	this->GameLoop();
}

void GameManager::LoadAndSetSystems()
{
	// load and shaders
	m_shaders["Fog"].InitShaders("fogShader");
	m_shaders["Basic"].InitShaders("basicShader");
	m_shaders["Toon"].InitShaders("toonShader");
	m_shaders["Rim_L"].InitShaders("RimLighting");
	
	// initialise gameobjects and load respective texture
	for (size_t i = 0; i < NUM_GAME_OBJECTS; i++)
	{
		m_gameObjects.emplace_back(GameObject());
	}

	m_gameObjects[FROG].InitGameObj("Frog", "FrogTex", 
		3.5f, -1.15f, 0.0f, 
		1.0f, 1.0f, 0.75f, 
		5.0f);
	m_gameObjects[BEE].InitGameObj("Bee", "BeeTex", 
		-3.5f, -1.15f, 0.0f, 
		1.0f, 1.0f, 1.0f, 
		5.0f);
	m_gameObjects[PUMPKIN].InitGameObj("Pumpkin", "PumpkinTex", 
		0.0f, 2.0f, 0.0f, 
		1.0f, 1.0f, 1.0f, 
		16.0f);

	SetShader(currentShader);
	m_backgroundAudio->PlayAudio();
}

void GameManager::GameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		this->ProcessInput();
		this->RenderScene();
	}
}

void GameManager::ProcessInput()
{
	SDL_Event m_evnt;

	while (SDL_PollEvent(&m_evnt) != 0)
	{
		if (m_evnt.type == SDL_QUIT)
		{
			m_gameState = GameState::EXIT;
		}

		switch (m_evnt.type)
		{	
		case SDL_KEYDOWN:

			switch (m_evnt.key.keysym.sym)
			{

			//shaders
			case SDLK_1:
				std::cout << "Fog Shader Active" << std::endl;
				currentShader = "Fog";
				SetShader(currentShader);
				break;

			case SDLK_2:
				std::cout << "Basic Shader Active" << std::endl;
				currentShader = "Basic";
				SetShader(currentShader);
				break;

			case SDLK_3:
				std::cout << "Toon Shader Active" << std::endl;
				currentShader = "Toon";
				SetShader(currentShader);
				break;

			case SDLK_4:
				std::cout << "Rim Lighting Shader Active" << std::endl;
				currentShader = "Rim_L";
				SetShader(currentShader);
				break;
				
			// game object selection
			case SDLK_i:
				selectedGameObj = FROG;
				std::cout << "Frog Game Object Selected!" << std::endl;
				break;

			case SDLK_o:
				selectedGameObj = BEE;
				std::cout << "Bee Game Object Selected!" << std::endl;
				break;

			case SDLK_p:
				selectedGameObj = PUMPKIN;
				std::cout << "Pumpkin Game Object Selected!" << std::endl;
				break;

			// movement
			case SDLK_w:
				m_gameObjects[selectedGameObj].MoveUp();
				break;

			case SDLK_s:
				m_gameObjects[selectedGameObj].MoveDown();
				break;

			case SDLK_a:
				m_gameObjects[selectedGameObj].MoveLeft();
				break;

			case SDLK_d:
				m_gameObjects[selectedGameObj].MoveRight();
				break;
			
			default:
				break;
			}

		default:
			break;
		}
	}
}

void GameManager::RenderScene()
{
	m_gameDisplay.ClearDisplay();

	if (Collided(m_gameObjects[selectedGameObj].GetObjPos(), m_gameObjects[selectedGameObj].GetObjRadius(), m_gameObjects[PUMPKIN].GetObjPos(), m_gameObjects[PUMPKIN].GetObjRadius()))
	{
		m_gameObjects[selectedGameObj].CollisionMove(m_gameObjects[PUMPKIN]);
	}

	for (GameObject& obj : m_gameObjects)
	{
		m_shaders[currentShader].UpdateUniforms(obj.GetObjTransform(), m_camera);
		obj.DrawGOwithTexture();
	}

	m_gameDisplay.SwapWindowBuffer();
}

// collision detection
bool GameManager::Collided(const glm::vec3 pos1, const float radius1, const glm::vec3 pos2, const float radius2)
{
	float distanceNotSqrd = ((pos1.x - pos2.x) * (pos1.x - pos2.x)) + ((pos1.y - pos2.y) * (pos1.y - pos2.y)) + ((pos1.z - pos2.z) * (pos1.z - pos2.z));
	float combinedRadius = radius1 + radius2;
	float distance = distanceNotSqrd * distanceNotSqrd;

	if (combinedRadius > distance)
	{
		m_collisionAudio->PlayAudio();

		return true;
	}

	return false;
}

// allows user to change shaders
// 1 = fog, 2 = basic, 3 = toon, 4 = rim lighting 
void GameManager::SetShader(const std::string& shaderName)
{
	m_shaders[shaderName].Bind();
}