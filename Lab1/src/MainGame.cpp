#include "MainGame.h"

//global variables
unsigned int indices[] = { 0, 1, 2 };
Transform transform;


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

	mesh2.LoadModel("..\\res\\monkey3.obj"); // might need .obj
	
	// texture
	texture.LoadTexture("..\\res\\bricks.jpg");

	// shader
	shader.SetUp("..\\res\\shader");

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
	
	// different from commented out because only one model is used instead of 2

	//Shader shader("..\\res\\shader"); //new shader
	//Texture texture.TextureLoad("..\\res\\bricks.jpg"); //load texture
	//Texture texture1("..\\res\\water.jpg"); //load texture

	transform.SetPos(glm::vec3(sinf(-counter), 0.0f, 0.0f));
	transform.SetRot(glm::vec3(0.0f, counter * 2.0f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	/*transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));*/

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh2.Draw();
	counter = counter + 0.01f;


	_gameDisplay.SwapBuffer();


	////triangle 1
	//Vertex vertices[] = { Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
	//					  Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 1.0f)),
	//					  Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)) 
	//};

	////triangle 2
	//Vertex vertices1[] = { Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
	//					  Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 1.0f)),
	//					  Vertex(glm::vec3(0.5f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)) 
	//};



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

	//

	//_gameDisplay.SwapBuffer(); // swap buffers
}