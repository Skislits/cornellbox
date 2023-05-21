#ifndef VIEW
#define VIEW

#include "SDL.h"
#include "glew.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "model.h"
#include "camera.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;
using namespace glm;

class View {
private:
	Model& model;
	GLuint mvp_uniform_attribute;
public:
	View(Model& model);
	Camera camera = Camera();
	void render(SDL_Window* window);
};

GLuint LoadShader(string shader_file_name, GLenum shader_type);

#endif
