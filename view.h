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
	GLuint light_position_uniform_attribute;
	GLuint camera_position_uniform_attribute;

	class SceneLoader {
	private:
		View& view;
		std::vector<float> rectangle_data_vector;
		void loadAllRectangles();
		void loadBlock(const Block& block);
		void loadRectangle(const Rectangle& rectangle);
		void loadRectangleVertex(const int& vertex_number, const Rectangle& rectangle, const vec3& vertex_normal);
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
	vec3 light_position = vec3(250.f, 250.f, 250.f);
};

GLuint LoadShader(std::string shader_file_name, GLenum shader_type);

#endif
