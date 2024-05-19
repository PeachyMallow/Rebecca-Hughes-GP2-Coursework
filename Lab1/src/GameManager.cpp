#include "GameManager.h"

//global variables
unsigned int indices[] = { 0, 1, 2 };

GLfloat GameObject::m_counter = 0.0f;

GameManager::GameManager() 
	: m_gameDisplay(1024, 768, glm::vec4(0.11f, 0.07f, 0.033f, 1.0f), "Scene Window"), 
	m_camera(glm::vec3(0, 0, -10), 70.0f, (float)m_gameDisplay.GetWidth() / m_gameDisplay.GetHeight(), 0.01f, 1000.0f),
	m_gameState(GameState::PLAY), mouseX(0), mouseY(0), m_frameCounter(0)
{
	// pre-allocates correct amount of memory needed for gameObjects per the enum in header
	// to prevent reallocation of memory once objects are added
	m_gameObjects.reserve(NUM_GAME_OBJECTS);

	m_backgroundAudio = new Audio("..\\res\\sounds\\background.wav");
	m_backgroundAudio->SetUpDevice();
	//m_BGAudioDev = m_backgroundAudio->GetAudioDevice();

	m_collisionAudio = new Audio("..\\res\\sounds\\bounce.wav");
	m_collisionAudio->SetUpDevice();
	m_BGAudioDev = m_collisionAudio->GetAudioLength();

//	//_gameState = static_cast<GameState>(GameState::PLAY); // IF USING MOVE TO SEPARATE FUNC? DO WE EVEN NEED GAMESTATE?
// 
//	_gameState = GameState::PLAY;
//
//	//std::unique_ptr<Display> _backDisplay = std::make_unique<Display>();
}

void GameManager::RunGame()
{
	this->LoadAndSetSystems(); // only runs once
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

	m_gameObjects[FROG].InitGameObj("Frog", "FrogTex", 2.0f, 0.0f, 4.0f);
	m_gameObjects[BEE].InitGameObj("Bee", "BeeTex", -2.0f, 0.0f, 4.0f);
	m_gameObjects[PUMPKIN].InitGameObj("Pumpkin", "PumpkinTex", 0.0f, 0.0f, 4.0f);


	SetShader(currentShader);

	//SetTransforms(FROG);
	//SetTransforms(BEE);
	//SetTransforms(PUMPKIN);
	//----
	//m_mesh[FROG].LoadModel("Frog");
	//m_mesh[BEE].LoadModel("Bee");
	//m_mesh[PUMPKIN].LoadModel("Pumpkin");
	//// texture
	//texture[FROG].LoadTexture("FrogTex");
	//texture[BEE].LoadTexture("BeeTex");
	//texture[PUMPKIN].LoadTexture("PumpkinTex");
	//----
	//m_shader.InitProgram();
	//m_shader[3].SetLightPos(m_Camera);
	//set lighting uniform here
	//m_shader[FROG].SetLightingUniform("u_lighting", m_Camera);
}

void GameManager::GameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		this->ProcessInput();
		this->DrawGame();
	}
}

void GameManager::ProcessInput()
{
	/*SDL_Event evnt;*/ // create SDL event

	while (SDL_PollEvent(&m_evnt) != 0) //SDL_PollEvent - Event Loop (a queue)
	{
		if (m_evnt.type == SDL_QUIT)
		{
			m_gameState = GameState::EXIT;
		}

		switch (m_evnt.type)
		{
			// maybe W & S to move object in and out then mouse to drag along pos x & y
			// PRINTING TWICE FOR SOME REASON
			
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

			case SDLK_w:
				std::cout << "moving up" << std::endl;
				m_backgroundAudio->PlayAudio();
				break;

			case SDLK_s:
				std::cout << "moving down" << std::endl;
				m_collisionAudio->PlayAudio();
				break;

			case SDLK_a:
				std::cout << "moving left" << std::endl;
				m_gameObjects[FROG].MoveLeft();
				break;

			case SDLK_d:
				std::cout << "moving right" << std::endl;
				break;

			
			
			
			default:
				break;
			}

		/*case SDL_KEYUP:*/

			//up 
			//if (keyStates[SDL_SCANCODE_1])
			//{
			//	std::cout << "Fog Shader Active" << std::endl;
			//	currentShader = "Fog";
			//	SetShader(currentShader);
			//}
			////down
			//if (keyStates[SDL_SCANCODE_2])
			//{
			//	std::cout << "Basic Shader Active" << std::endl;
			//	currentShader = "Basic";
			//	SetShader(currentShader);
			//}
			//right
			//if (keyStates[SDL_SCANCODE_3])
			//{
			//	std::cout << "Toon Shader Active" << std::endl;
			//	currentShader = "Toon";
			//	SetShader(currentShader);
			//}
			////left
			//if (keyStates[SDL_SCANCODE_4])
			//{
			//	std::cout << "Rim Lighting Shader Active" << std::endl;
			//	currentShader = "Rim_L";
			//	SetShader(currentShader);
			//}

		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouseX, &mouseY);

			//std::cout << "mouse x: " << mouseX << "mouse y: " << mouseY << std::endl;
			break;


		case SDL_MOUSEBUTTONDOWN:
			
			if (m_evnt.button.button == SDL_BUTTON_LEFT)
			{
				//std::cout << "Left mouse button clicked!" << std::endl;
			}

			break;
			// case SDL_MOUSEBUTTONUP

		case SDL_MOUSEWHEEL:

			if (m_evnt.wheel.y > 0)
			{
				//std::cout << "wheel scrolling up" << std::endl;
			}

			if (m_evnt.wheel.y < 0)
			{
				//std::cout << "wheel scrolling down" << std::endl;
			}
			break;

		default:
			break;
		}

		//SDL_Delay(50); // maybe keep? 
	}

	
}

void GameManager::DrawGame()
{
	m_gameDisplay.ClearDisplay();
	
	AudioStatus();
	// check for collision here?
//if (Collided(transform1.GetPos(), mesh1.GetRadius(), transform2.GetPos(), mesh2.GetRadius()))
//{	
//	//std::cout << "Model 1 radius: " << mesh1.GetRadius() << std::endl;
//	//std::cout << "Model 2 radius: " << mesh2.GetRadius() << std::endl;
//}
// if pos reaches edge of window then turn back

	m_shaders[currentShader].SetLightPos(m_camera);

	for (GameObject& obj : m_gameObjects)
	{
		m_shaders[currentShader].UpdateLight(obj.GetObjTransform(), m_camera);
		m_shaders[currentShader].Update(obj.GetObjTransform(), m_camera);
		obj.DrawGOwithTexture();
		obj.Move(obj);
	}

	m_gameObjects[FROG].IncrementCounter(0.00001f); // needed?


	//------------^
	
	//------------
	// for each object to have a different:
	// shader, texture, transform, & texture
	//for (int i = 0; i < NUM_OBJECTS; i++)
	//{
	//	SetTransforms(i); // done
	//	SetShader(i);
	//	m_shader[i].Update(transform[i], m_Camera);
	//	texture[i].Bind(0); // done
	//	m_mesh[i].Draw(); // done
	//}
	//counter = counter + 0.005f;
	//------------^

	
	m_frameCounter = m_frameCounter + 0.005f;
	m_gameDisplay.SwapWindowBuffer();
}

void GameManager::AudioStatus()
{
	//m_backgroundAudio->GetAudioDevice
	Uint32 length = m_BGAudioDev;
	//std::cout << length << std::endl;

	if (length == 0)
	{
		std::cout << length << std::endl;
	}
	/*switch (SDL_GetAudioDeviceStatus(m_BGAudioDev))
	{
	case SDL_AUDIO_STOPPED: std::cout << ("stopped\n") << std::endl; break;
	case SDL_AUDIO_PLAYING: std::cout << ("playing\n") << std::endl; break;
	case SDL_AUDIO_PAUSED: std::cout << ("paused\n") << std::endl; break;
	default: std::cout << ("???") << std::endl; break;
	}*/
}

// collision detection               MIGHT NOT NEED ONE OF THE AXIS?
bool GameManager::Collided(const glm::vec3 pos1, const float radius1, const glm::vec3 pos2, const float radius2)
{
	//if radius1 + radius2 < distance from centre points then colliding
	// distance = ((x1 + x2) * (x1 + x2)) + ((y1 + y2) * (y1 + y2)) + ((z1 + z2) * (z1 + z2))
	float distanceNotSqrd = ((pos1.x - pos2.x) * (pos1.x - pos2.x)) + ((pos1.y - pos2.y) * (pos1.y - pos2.y)) + ((pos1.z - pos2.z) * (pos1.z - pos2.z));
	float combinedRadius = radius1 + radius2;

	float distance = distanceNotSqrd * distanceNotSqrd;

	//float sum = distance - combinedRadius; // temp for cout? 
	/*std::cout << "Distance Sqrd: " << distance << std::endl;
	std::cout << "Distance Not Sqrd: " << distanceNotSqrd << std::endl;*/

	if (combinedRadius > distance)
	{
		std::cout << "Objects have collided!" << std::endl;
		return true;
	}

	//std::cout << "Objects are not colliding" << std::endl;
	return false;
}

//void GameManager::SetTransforms(int objectType)
//{
//	switch (objectType)
//	{
//	case FROG:
//		/*transform[FROG].SetPos(glm::vec3(0.0f, 0.0f, sinf(counter) * 4.0f));
//		transform[FROG].SetRot(glm::vec3(0.0f, counter * 1.0f, 0.0f));
//		transform[FROG].SetScale(glm::vec3(2.0f, 2.0f, 2.0f));*/
//		
//		transform[FROG].SetPos(glm::vec3(sinf(counter), 0.0f, -2.0f));
//		transform[FROG].SetRot(glm::vec3(0.0f, 0.0f /*counter * 1.0f*/, 0.0f));
//		transform[FROG].SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
//
//		break;
//
//	case BEE:
//		transform[BEE].SetPos(glm::vec3(counter - 4.0f, 0.0f, 3.0f));
//		transform[BEE].SetRot(glm::vec3(0.0f, -counter * 1.0f, 0.0f));
//		transform[BEE].SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
//		break;
//
//	case PUMPKIN:
//		//transform[PUMPKIN].SetPos(glm::vec3(/*counter - 0.0f*/ 3.0f, 1.0f, 3.0f));
//		//transform[PUMPKIN].SetRot(glm::vec3(0.0f, 0.0f /*counter * 1.0f*/, 0.0f));
//		//transform[PUMPKIN].SetScale(glm::vec3(0.75f, 0.75f, 0.75f));
//		transform[PUMPKIN].SetPos(glm::vec3(0.0f, 2.0f, /*sinf(counter) * */3.0f));
//		transform[PUMPKIN].SetRot(glm::vec3(0.0f, 0.0f, 0.0f)); // still
//		//transform[PUMPKIN].SetRot(glm::vec3(0.0f, counter * 1.0f, 0.0f)); // rotate
//		transform[PUMPKIN].SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
//
//
//		break;
//	}
//}

void GameManager::SetShader(const std::string& shaderName)
{
	m_shaders[shaderName].Bind();
}

//void GameManager::SetTexture()
//{
//
//}


////access number of elements in array by dividing the size of the array by the size of the data type it contains
////sizeof() returns the size of a type in bytes
//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0])); //create a mesh object 
//Shader shader("..\\res\\shader"); //create a shader
//Texture texture("..\\res\\bricks.jpg"); //load texture
//
//Transform transform; 
//transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
//transform.SetRot(glm::vec3(0.0, 0.0, -counter * 5)); 
//transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));
//
//shader.Bind(); //bind the shader
//shader.Update(transform); 
//texture.Bind(0);
//mesh.Draw(); //draw the mesh