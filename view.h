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

class View {
private:
	Model& model;
	GLuint mvp_uniform_attribute;
	GLuint shader_program;

	class SceneLoader {
	private:
		View& view;
		std::vector<float> rectangle_data_vector;
		void loadAllRectangles();
		void loadBlock(const Block& block);
		void loadRectangle(const Rectangle& rectangle);
		void loadRectangleVertex(const int& vertex_number, const Rectangle& rectangle);
	public:
		GLuint number_of_vertices_in_scene;
		SceneLoader(View& view);
	};
	SceneLoader* scene_loader;
public:
	View(Model& model);
	~View();
	Camera camera = Camera();
	void render(SDL_Window* window);
};

GLuint LoadShader(std::string shader_file_name, GLenum shader_type);

#endif
