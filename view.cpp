#include "view.h"

View::View(Model& model) : model(model) {
	// let OpenGL uses the z-values to determine what is in front of what
	glEnable(GL_DEPTH_TEST);

	// creates two compiled shader objects
	GLuint vertex_shader = LoadShader(std::string("GLSL/vertex_shader.txt"), GL_VERTEX_SHADER);
	GLuint fragment_shader = LoadShader(std::string("GLSL/fragment_shader.txt"), GL_FRAGMENT_SHADER);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	// tells the program object to look in the fragment shader for the out variable "color_out" and use it to color the back buffer
	glBindFragDataLocation(shader_program, 0, "color_out");
	
	glLinkProgram(shader_program);
	GLint link_status;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE) {
		std::cout << "shader linker error in View constructor" << std::endl;
		char buffer[512];
		glGetProgramInfoLog(shader_program, 512, nullptr, buffer);
	}

	// free resources
	glDetachShader(shader_program, vertex_shader);
	glDetachShader(shader_program, fragment_shader);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// tell OpenGL to start using program
	glUseProgram(shader_program);

	// get a handle to the "mvp" variable in shader program
	mvp_uniform_attribute = glGetUniformLocation(shader_program, "mvp");

	scene_loader = new SceneLoader(*this);
}

View::~View() {
	delete scene_loader;
}

void View::render(SDL_Window* window) {
	// clear color and depth buffer, in order the camera might have moved
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.updateViewMatrix();

	// MVP matrix
	glm::mat4 model_view_projection = camera.projection_matrix * camera.view_matrix;

	glUniformMatrix4fv(mvp_uniform_attribute, 1, GL_FALSE, &model_view_projection[0][0]);

	// render object from buffer
	glDrawArrays(GL_TRIANGLES, 0, (*scene_loader).number_of_vertices_in_scene);

	// force execution of GL commands in finite time
	glFlush();

	// used with double-buffered OpenGL contexts to swap context
	SDL_GL_SwapWindow(window);
}

GLuint LoadShader(std::string shader_file_name, GLenum shader_type) {
	std::ifstream my_stream(shader_file_name); // standard library input file stram for reading the shader file
	std::string contents = std::string((std::istreambuf_iterator<char>(my_stream)), std::istreambuf_iterator<char>()); // reads the entire file into a string
	const GLchar* shader_code = contents.c_str(); // convert the string object to a GLchar array
	
	GLuint shader = glCreateShader(shader_type); // creates a shader object of the specified type, e.g. fragment or vertex shader
	glShaderSource(shader, 1, &shader_code, nullptr); // loads the shader code into the shader object
	glCompileShader(shader);

	// check if shader compiled correctly
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		std::cout << "shader compile error in: " << shader_file_name << std::endl;
		char buffer[512];
		glGetShaderInfoLog(shader, 512, nullptr, buffer);
		std::cout << buffer << std::endl;
	}

	// return the handle to the shader
	return shader;
}

void View::SceneLoader::loadAllRectangles() {
	loadRectangle(view.model.scene_floor);
	loadRectangle(view.model.scene_ceiling);
	loadRectangle(view.model.scene_back_wall);
	loadRectangle(view.model.scene_right_wall);
	loadRectangle(view.model.scene_left_wall);
	
	loadBlock(view.model.short_block);
	loadBlock(view.model.tall_block);
}

void View::SceneLoader::loadBlock(const Block& block) {
	for (size_t i = 0; i < block.block_sides.size(); i++) {
		loadRectangle(block.block_sides[i]);
	}
}

void View::SceneLoader::loadRectangle(const Rectangle& rectangle) {
	// rectangle is rendered as two triangles
	loadRectangleVertex(0, rectangle);
	loadRectangleVertex(1, rectangle);
	loadRectangleVertex(2, rectangle);
	loadRectangleVertex(0, rectangle);
	loadRectangleVertex(2, rectangle);
	loadRectangleVertex(3, rectangle);
}

void View::SceneLoader::loadRectangleVertex(const int& vertex_number, const Rectangle& rectangle) {
	for (size_t j = 0; j < 3; j++) {
		rectangle_data_vector.push_back(rectangle[vertex_number][j]);
	}
	for (size_t i = 0; i < 3; i++) {
		rectangle_data_vector.push_back(rectangle.RGB_color[i]);
	}
}

View::SceneLoader::SceneLoader(View& view) :view(view) {
	loadAllRectangles();

	float* rectangle_data_array = new float[rectangle_data_vector.size()];
	for (size_t i = 0; i < rectangle_data_vector.size(); i++) {
		rectangle_data_array[i] = rectangle_data_vector[i];
	}

	number_of_vertices_in_scene = rectangle_data_vector.size() / 2; // half of the data is color data

	// create vertex array object (VAO) for storing settings
	// VAO stores how data should be read, what format the data is, 
	// were it should go in the shaders, etc., but it doesn't store actual data
	GLuint vertex_array_object;
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	// create vertex buffer object (VBO), get a handle to the buffer, load rectangles vertices into the buffer
	GLuint rectangle_buffer;
	glGenBuffers(1, &rectangle_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, rectangle_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectangle_data_vector.size(), rectangle_data_array, GL_STATIC_DRAW);

	delete[] rectangle_data_array;

	// get a handle to the "vertex_position" input attribute, tell it to read 3 floats at a time
	// for the variable related to vertex_position_attribute, give it three data values
	// data of the form floats, data which shouldn't be normalized, data which comes in chunks of 6
	// take the three data values stating from byte 0 in such a chunk
	GLint vertex_position_attrib = glGetAttribLocation(view.shader_program, "vertex_position");
	glVertexAttribPointer(vertex_position_attrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(vertex_position_attrib);

	// get a handle to the "color_input" input attribute, tell it to read 3 floats at a time
	GLint texture_coordinate_attrib = glGetAttribLocation(view.shader_program, "color_input");
	glVertexAttribPointer(texture_coordinate_attrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
		(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(texture_coordinate_attrib);
}
