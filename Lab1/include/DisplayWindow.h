#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <glm\glm.hpp>

#include <iostream>

class DisplayWindow
{
	const void ErrorHandler(const std::string& errorString);

	SDL_Window* m_window;
	int m_windowWidth;
	int m_windowHeight;

	glm::vec4 m_sceneBGColour; // scene background colour

public:
	DisplayWindow(const int windowWidth, const int windowHeight, const glm::vec4 sceneColour, const char* windowTitle);
	~DisplayWindow();

	void ClearDisplay();
	void SwapWindowBuffer();

	const GLuint GetWidth() const { return m_windowWidth; }
	const GLuint GetHeight() const { return m_windowHeight; }

	SDL_GLContext m_glContext;
};