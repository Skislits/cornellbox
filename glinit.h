#ifndef GLINIT_H
#define GLINIT_H

#include <SDL.h>
#include <glew.h>
#include <iostream>

using namespace std;

/*
* Create a window, initialize a GL context and initialize the GLEW library
*/
void init(SDL_Window*& window);

#endif
