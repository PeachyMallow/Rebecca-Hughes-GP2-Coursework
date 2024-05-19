#pragma once

#include <SDL/SDL.h>
#include <GL\glew.h> // does SDL have to come before glew? 

#include <iostream>
//#include <string>

class Display
{
	void ReturnError(std::string errorString);

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;

public:
	//Display() : _window(nullptr), _screenWidth(1024), _screenHeight(768), glContext(nullptr) {};// <---- USING??
	Display(int windowWidth, int windowHeight, const char* windowTitle);
	~Display();

	void InitDisplay();
	void ClearDisplay(float r, float g, float b, float a);
	void SwapBuffer();

	SDL_GLContext glContext;
	
	GLuint GetWidth() { return _screenWidth; }
	GLuint GetHeight() { return _screenHeight; }
};