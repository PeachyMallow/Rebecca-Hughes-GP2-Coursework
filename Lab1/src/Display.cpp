#include "Display.h"

// issue with passing the parameters when creating _gameDisplay in MainGame.h
Display::Display(float windowWidth, float windowHeight, const std::string& windowTitle)
	: _screenWidth(windowWidth), _screenHeight(windowHeight)
{
	//_screenWidth = windowWidth;// <-- might not be needed? Only using to remove init func on here
	//_screenHeight = windowHeight;// <--

	_window = nullptr;
	_screenWidth = static_cast<float>(1024);
	_screenHeight = static_cast<float>(768);
	glContext = nullptr;

	//// initialise SDL library & all (?) subsystems
	// // maybe change from 'everything' when we know what we're making specifically
	//if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { ReturnError("Error initialising SDL"); }

	//// are the colours set up? v BTB #2 video windows
	//// double buffering, 1 enables
	//if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0) { ReturnError("Error setting up the double buffers"); }

	//// create window
	//_window = SDL_CreateWindow(windowTitle.c_str(),
	//	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	//	static_cast<int>(_screenWidth), static_cast<int>(_screenHeight), SDL_WINDOW_OPENGL);

	//// could this be wrapped around above code? _window -> SDL_WINDOW_OPENGL
	//if (_window == nullptr) { ReturnError("error in initialising _window"); }

	//// create context
	//glContext = SDL_GL_CreateContext(_window);

	//// could this v be wrapped around above code? ^ glContext line
	//if (glContext == nullptr) { ReturnError("error in creating glContext"); }

	//GLenum error = glewInit();

	//if (error != GLEW_OK) { ReturnError("error in initialising GLEW"); }


	//glEnable(GL_DEPTH_TEST); //enable z-buffering 
	//glEnable(GL_CULL_FACE); // don't draw faces that are not pointing at the camera

	//// set background colour - red, green, blue, alpha
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);



	// here for initialising member variables?
	/*_window = nullptr;*/ //initialise to generate null access violation for debugging. 
	/*_screenWidth = 1024*/;
	/*_screenHeight = 768*/; 
}

Display::~Display() // cross checked with BTB video #2
{
	SDL_GL_DeleteContext(glContext); // must delete context before window
	SDL_DestroyWindow(_window); 
	SDL_Quit();
}

void Display::ReturnError(std::string errorString) // called in this script
{
	std::cout << errorString << std::endl;
	std::cout << SDL_GetError() << std::endl;
	std::cout << "Press any key to quit.." << std::endl;
	std::cin.get();
	SDL_Quit();
}

//init display func

void Display::InitDisplay() // called in MainGame.cpp
{
	// initialise SDL library & all (?) subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // maybe change from 'everything' when we know what we're making specifically
	{
		ReturnError("Error initialising SDL");
	}
	
	// double buffering, 1 enables
	if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0) // are the colours set up? BTB #2 video windows
	{
		ReturnError("Error setting up the double buffers");
	}
	
	// create window
	_window = SDL_CreateWindow("Game Window",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	
	if (_window == nullptr) // could this be wrapped around above code? _window -> SDL_WINDOW_OPENGL
	{
		ReturnError("error in initialising _window");
	}
	// create context
	glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)// could this be wrapped around above code? glContext line
	{
		ReturnError("error in creating glContext");
	}
	
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		ReturnError("error in initialising GLEW");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); // don't draw faces that are not pointing at the camera

	// set background colour - red, green, blue, alpha
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

void Display::SwapBuffer() // called in MainGame.cpp
{
	SDL_GL_SwapWindow(_window);
}

void Display::ClearDisplay(float r, float g, float b, float a) // called in MainGame.cpp
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}