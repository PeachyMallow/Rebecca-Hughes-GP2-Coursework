#pragma once

#include <GL\glew.h> // does SDL have to come before glew? 
#include <SDL/SDL.h>

#include <iostream>
#include <string>

class Display
{
	void ReturnError(std::string errorString);

	SDL_Window* _window; // window pointer
	int _screenWidth; // both width & height are floats in Lab 4
	int _screenHeight;// do we need these these to be ints instead of casting to floats?

public:
	Display() : _window(nullptr), _screenWidth(1024), _screenHeight(768), glContext(nullptr) {};
	Display(int windowWidth, int windowHeight, const std::string& windowTitle);// <---- NOT USED, EITHER WORK OUT HOW TO USE OR DELETE
	~Display();

	void InitDisplay();
	void ClearDisplay(float r, float g, float b, float a);
	void SwapBuffer();

	SDL_GLContext glContext;
	
	GLuint GetWidth() { return _screenWidth; }
	GLuint GetHeight() { return _screenHeight; }
};