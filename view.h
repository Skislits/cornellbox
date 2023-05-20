#ifndef VIEW
#define VIEW

#include "SDL.h"
#include "glew.h"
#include "model.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class View {
private:
	Model& model;
public:
	View(Model& model);
	void render(SDL_Window* window);
};

GLuint LoadShader(string shader_file_name, GLenum shader_type);

#endif
