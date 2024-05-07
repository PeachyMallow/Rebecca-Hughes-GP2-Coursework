#pragma once

#include <GL\glew.h> // does SDL have to come before glew? 
#include <SDL/SDL.h>

#include <iostream>
#include <string>

class Display
{
	void ReturnError(std::string errorString);

	SDL_Window* _window; //holds pointer to out window
	//int _screenWidth; // both width & height are floats in Lab 4
	//int _screenHeight;// do we need these these to be ints instead of casting to floats?
	float _screenWidth; // both width & height are floats in Lab 4
	float _screenHeight;// do we need these these to be ints instead of casting to floats?

public:
	Display() : _window(nullptr), _screenWidth(1024), _screenHeight(768), glContext(nullptr) {};
	Display(float windowWidth, float windowHeight, const std::string& windowTitle) /*: _window(nullptr), _screenWidth(1024), _screenHeight(768), glContext(nullptr) {}*/;
	~Display();

	void InitDisplay();
	void SwapBuffer();
	void ClearDisplay(float r, float g, float b, float a);
	SDL_GLContext glContext;
	
	float GetWidth() { return _screenWidth; }
	float GetHeight() { return _screenHeight; }
};