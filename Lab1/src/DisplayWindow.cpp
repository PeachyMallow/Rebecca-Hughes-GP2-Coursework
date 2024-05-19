#include "DisplayWindow.h"

DisplayWindow::DisplayWindow(const int windowWidth, const int windowHeight, const glm::vec4 sceneColour, const char* windowTitle)
	: m_window(nullptr), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_sceneBGColour(sceneColour), m_glContext(nullptr)
{ 
	// initialise SDL library & all (?) subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // maybe change from 'everything' when we know what we're making specifically
	{
		ErrorHandler("Error initialising SDL");
	}

	// double buffering, 1 enables
	if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0) // are the colours set up? BTB #2 video windows
	{
		ErrorHandler("Error setting up the double buffers");
	}

	// create window
	m_window = SDL_CreateWindow(windowTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL);

	if (m_window == nullptr) // could this be wrapped around above code? _window -> SDL_WINDOW_OPENGL
	{
		ErrorHandler("error in initialising _window");
	}

	// create context
	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == nullptr)// could this be wrapped around above code? glContext line
	{
		ErrorHandler("error in creating glContext");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		ErrorHandler("error in initialising GLEW");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); // don't draw faces that are not pointing at the camera

	glClearColor(m_sceneBGColour.x, m_sceneBGColour.y, m_sceneBGColour.z, m_sceneBGColour.w);
}

// sets scene background colour
// clears colour & depth buffer
void DisplayWindow::ClearDisplay()
{
	glClearColor(m_sceneBGColour.x, m_sceneBGColour.y, m_sceneBGColour.z, m_sceneBGColour.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

DisplayWindow::~DisplayWindow()
{
	SDL_GL_DeleteContext(m_glContext); // must delete context before window
	SDL_DestroyWindow(m_window); 
	SDL_Quit();
}

// handles printing errors to console during DisplayWindow initialisation in constructor
const void DisplayWindow::ErrorHandler(const std::string& errorString)
{
	std::cout << errorString << std::endl;
	std::cout << SDL_GetError() << std::endl;
	std::cout << "Press any key to quit.." << std::endl;
	std::cin.get();
	SDL_Quit();
}

void DisplayWindow::SwapWindowBuffer()
{
	SDL_GL_SwapWindow(m_window);
}