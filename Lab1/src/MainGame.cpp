#include "MainGame.h"

//global variables
unsigned int indices[] = { 0, 1, 2 };
Transform transform[3];
//Transform transform2;
//Transform transform3;


MainGame::MainGame() : _gameDisplay(1024, 768, "Game Window"), _gameState(GameState::PLAY), counter(0)/*, mesh(), mesh1(), mesh2(), myCamera()*/
{
	//Mesh newMesh; // change name?
	//Camera camera;

//	//_gameState = static_cast<GameState>(GameState::PLAY); // IF USING MOVE TO SEPARATE FUNC? DO WE EVEN NEED GAMESTATE?
// 
//	_gameState = GameState::PLAY;
//
//	//Display* _backDisplay = new Display(1024, 768, "Labs"); // will need to delete at some point
//	//std::unique_ptr<Display> _backDisplay = std::make_unique<Display>();
}

MainGame::~MainGame()
{
}

void MainGame::Run()
{
	this->InitSystems(); // only runs once
	this->GameLoop();
}

void MainGame::InitSystems()
{
	_gameDisplay.InitDisplay();

	m_mesh[FROG].LoadModel("Frog");
	m_mesh[BEE].LoadModel("Bee");
	m_mesh[PUMPKIN].LoadModel("Pumpkin");

	// texture
	texture[FROG].LoadTexture("FrogTex");
	texture[BEE].LoadTexture("BeeTex");
	texture[PUMPKIN].LoadTexture("PumpkinTex");

	//m_shader.InitProgram();

	// shaders
	m_shader[FROG].InitShaders("toonShader");
	m_shader[BEE].InitShaders("basicShader");
	//m_shader[PUMPKIN].InitShaders("toonShader");
	m_shader[PUMPKIN].InitShaders("RimLighting");
	

	m_Camera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.GetWidth() / _gameDisplay.GetHeight(), 0.01f, 1000.0f);

	//counter
}

void MainGame::GameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		this->ProcessInput();
		this->DrawGame();
	}
}

void MainGame::ProcessInput()
{
	SDL_Event evnt; // create SDL event

	const Uint8* keyStates = SDL_GetKeyboardState(NULL); // video
	std::string inputText;// video

	while (SDL_PollEvent(&evnt) /* != 0 */) //SDL_PollEvent - Event Loop (a queue)
	{
		if (evnt.type == SDL_QUIT)
		{
			_gameState = GameState::EXIT;
		}

		if (keyStates[SDL_SCANCODE_W])// video
		{
			std::cout << "W Pressed" << std::endl;
		}
	}

	SDL_GetMouseState(&mouseX, &mouseY);

	//std::cout << "mouse x: " << mouseX << "mouse y: " << mouseY << std::endl;
}

//while (SDL_PollEvent(&evnt) /* != 0 */) //SDL_PollEvent - Event Loop (a queue)
//{
//	switch (evnt.type)
//	{
//	case SDL_QUIT:
//		_gameState = GameState::EXIT;
//		break;

void MainGame::DrawGame()
{
	_gameDisplay.ClearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	// check for collision here?
	//if (Collided(transform1.GetPos(), mesh1.GetRadius(), transform2.GetPos(), mesh2.GetRadius()))
	//{	
	//	//std::cout << "Model 1 radius: " << mesh1.GetRadius() << std::endl;
	//	//std::cout << "Model 2 radius: " << mesh2.GetRadius() << std::endl;
	//}

	// if pos reaches edge of window then turn back
	
	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		SetTransforms(i);
		SetShader(i);
		m_shader[i].Update(transform[i], m_Camera);
		texture[i].Bind(0);
		m_mesh[i].Draw();
	}
	////model 1 - frog
	//SetTransforms(FROG);
	//SetShader(FOG);
	//m_shader[FROG].Update(transform[FROG], m_Camera);
	//texture[FROG].Bind(0);
	//m_mesh[FROG].Draw();
	////model 2 - bee
	//SetTransforms(BEE);
	//SetShader(BASIC);
	//m_shader[BEE].Update(transform[BEE], m_Camera);
	//texture[BEE].Bind(0);
	//m_mesh[BEE].Draw();
	////model 2 - pumpkin
	//SetTransforms(PUMPKIN);
	//SetShader(TOON);
	//m_shader[PUMPKIN].Update(transform[PUMPKIN], m_Camera);
	//texture[PUMPKIN].Bind(0);
	//m_mesh[PUMPKIN].Draw();

	counter = counter + 0.005f;

	_gameDisplay.SwapBuffer();
}

// collision detection               MIGHT NOT NEED ONE OF THE AXIS?
bool MainGame::Collided(glm::vec3 pos1, float radius1, glm::vec3 pos2, float radius2)
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

void MainGame::SetTransforms(int objectType)
{
	switch (objectType)
	{
	case FROG:
		/*transform[FROG].SetPos(glm::vec3(0.0f, 0.0f, sinf(counter) * 4.0f));
		transform[FROG].SetRot(glm::vec3(0.0f, counter * 1.0f, 0.0f));
		transform[FROG].SetScale(glm::vec3(2.0f, 2.0f, 2.0f));*/
		
		transform[FROG].SetPos(glm::vec3(2.0f, 0.0f, 1.0f));
		transform[FROG].SetRot(glm::vec3(0.0f, 0.0f /*counter * 1.0f*/, 0.0f));
		transform[FROG].SetScale(glm::vec3(2.0f, 2.0f, 2.0f));

		break;

	case BEE:
		transform[BEE].SetPos(glm::vec3(counter - 4.0f, 0.0f, 3.0f));
		transform[BEE].SetRot(glm::vec3(0.0f, -counter * 1.0f, 0.0f));
		transform[BEE].SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
		break;

	case PUMPKIN:
		//transform[PUMPKIN].SetPos(glm::vec3(/*counter - 0.0f*/ 3.0f, 1.0f, 3.0f));
		//transform[PUMPKIN].SetRot(glm::vec3(0.0f, 0.0f /*counter * 1.0f*/, 0.0f));
		//transform[PUMPKIN].SetScale(glm::vec3(0.75f, 0.75f, 0.75f));
		transform[PUMPKIN].SetPos(glm::vec3(0.0f, 0.0f, sinf(counter) * 3.0f));
		//transform[PUMPKIN].SetRot(glm::vec3(0.0f, 0.0f, 0.0f)); // still
		transform[PUMPKIN].SetRot(glm::vec3(0.0f, counter * 1.0f, 0.0f)); // rotate
		transform[PUMPKIN].SetScale(glm::vec3(0.75f, 0.75f, 0.75f));


		break;
	}
}

void MainGame::SetShader(int shaderType)
{
	switch (shaderType)
	{
	case FOG:
		m_shader[FOG].Bind();
		break;

	case BASIC:
		m_shader[BASIC].Bind();
		break;

	case TOON:
		m_shader[TOON].Bind();
		break;
	}
}

void MainGame::SetTexture()
{

}


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