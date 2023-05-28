#ifndef GLINIT_H
#define GLINIT_H

#include "SDL.h"
#include "glew.h"
#include "SDL_opengl.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

using namespace std;

/*
* Create a window, initialize a GL context and initialize the GLEW library
*/
void init(SDL_Window*& window);

#endif
