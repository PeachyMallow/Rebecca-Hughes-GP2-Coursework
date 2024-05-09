#include "MainGame.h"

//global variables
unsigned int indices[] = { 0, 1, 2 };
Transform transform1;
Transform transform2;
Transform transform3;


MainGame::MainGame() : _gameDisplay(1024, 768, "Game Window"), _gameState(GameState::PLAY), counter(0)/*, mesh(), mesh1(), mesh2(), myCamera()*/
{
	//Mesh newMesh; // change name?
	//Camera camera;

//	//_gameState = static_cast<GameState>(GameState::PLAY);
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
	this->InitSystems(); // once this has been initialised, does it need to keep getting initialised?
	this->GameLoop();
}

void MainGame::InitSystems()
{
	_gameDisplay.InitDisplay();

	mesh1.LoadModel("..\\res\\Frog.obj");

	mesh2.LoadModel("..\\res\\Bee.obj");

	mesh3.LoadModel("..\\res\\Pumpkin.obj");

	// texture
	texture.LoadTexture("..\\res\\FrogTex.png");
	texture2.LoadTexture("..\\res\\BeeTex.png");
	texture3.LoadTexture("..\\res\\PumpkinTex.png");

	// shader
	shader.SetUp("..\\res\\shader");
	shader2.SetUp("..\\res\\shader");
	shader3.SetUp("..\\res\\shader");

	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.GetWidth() / _gameDisplay.GetHeight(), 0.01f, 1000.0f);

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

	while (SDL_PollEvent(&evnt) /* != 0 */) //SDL_PollEvent - Event Loop (a queue)
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		}
	}
}

// will be updating to load from file
void MainGame::DrawGame()
{
	_gameDisplay.ClearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	// check for collision here?
	if (Collided(transform1.GetPos(), mesh1.GetRadius(), transform2.GetPos(), mesh2.GetRadius()))
	{	
		//std::cout << "Model 1 radius: " << mesh1.GetRadius() << std::endl;
		//std::cout << "Model 2 radius: " << mesh2.GetRadius() << std::endl;
	}

	// if pos reaches edge of window then turn back
	
	//model 1 - frog
	transform1.SetPos(glm::vec3(-counter + 4.0f, 0.0f, 3.0f));
	transform1.SetRot(glm::vec3(0.0f, counter * 1.0f, 0.0f));
	transform1.SetScale(glm::vec3(2.0f, 2.0f, 2.0f));

	/*transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));*/

	shader.Bind();
	shader.Update(transform1, myCamera);
	texture.Bind(0);
	mesh1.Draw(); // model 1

	//model 2 - bee
	transform2.SetPos(glm::vec3(counter - 4.0f, 0.0f, 3.0f));
	transform2.SetRot(glm::vec3(0.0f, -counter * 1.0f, 0.0f));
	transform2.SetScale(glm::vec3(0.5f, 0.5f, 0.5f));

	shader2.Bind();
	shader2.Update(transform2, myCamera);
	texture2.Bind(0);
	mesh2.Draw(); // model 2


	//model 2 - pumpkin
	transform3.SetPos(glm::vec3(counter - 0.0f, 0.0f, 3.0f));
	transform3.SetRot(glm::vec3(0.0f, counter * 1.0f, 0.0f));
	transform3.SetScale(glm::vec3(0.75f, 0.75f, 0.75f));

	shader3.Bind();
	shader3.Update(transform3, myCamera);
	texture3.Bind(0);
	mesh3.Draw(); // model 2

	counter = counter + 0.005f;

	_gameDisplay.SwapBuffer();


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
	//Mesh mesh1(vertices1, sizeof(vertices1) / sizeof(vertices1[0])); //create a mesh object 
	//Shader shader1("..\\res\\shader"); //create a shader
	//Texture texture1("..\\res\\water.jpg"); //load texture
	//Transform transform1;
	//transform1.SetPos(glm::vec3(sinf(-counter), 0.0, 0.0));
	//transform1.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	//transform1.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));
	//shader1.Bind();
	//shader1.Update(transform1);
	//texture1.Bind(1);
	//mesh1.Draw();
	//counter = counter + 0.01f;
	//_gameDisplay.SwapBuffer(); // swap buffers
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