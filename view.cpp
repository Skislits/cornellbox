#include "view.h"

View::View(Model& model) : model(model) {
	// creates two compiled shader objects
	GLuint vertex_shader = LoadShader(string("GLSL/vertex_shader.txt"), GL_VERTEX_SHADER);
	GLuint fragment_shader = LoadShader(string("GLSL/fragment_shader.txt"), GL_FRAGMENT_SHADER);

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	// tells the program object to look in the fragment shader for the out variable "color_out" and use it to color the back buffer
	glBindFragDataLocation(shader_program, 0, "color_out"); 

	glLinkProgram(shader_program);
	GLint link_status;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE) {
		cout << "shader linker error in View constructor" << endl;
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
}

void View::render(SDL_Window* window) {
	SDL_GL_SwapWindow(window);
}

GLuint LoadShader(string shader_file_name, GLenum shader_type) {
	ifstream my_stream(shader_file_name); // standard library input file stram for reading the shader file
	string contents = string((istreambuf_iterator<char>(my_stream)), istreambuf_iterator<char>()); // reads the entire file into a string
	const GLchar* shader_code = contents.c_str(); // convert the string object to a GLchar array
	
	GLuint shader = glCreateShader(shader_type); // creates a shader object of the specified type, e.g. fragment or vertex shader
	glShaderSource(shader, 1, &shader_code, nullptr); // loads the shader code into the shader object
	glCompileShader(shader);

	// check if shader compiled correctly
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		cout << "shader compile error in: " << shader_file_name << endl;
		char buffer[512];
		glGetShaderInfoLog(shader, 512, nullptr, buffer);
		cout << buffer << endl;
	}

	// return the handle to the shader
	return shader;
}