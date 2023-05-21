#include "view.h"

View::View(Model& model) : model(model) {
	// let OpenGL uses the z-values to determine what is in front of what
	glEnable(GL_DEPTH_TEST);

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

	// create vertex array object (VAO) for storing settings
	// VAO stores how data should be read, what format the data is, 
	// were it should go in the shaders, etc., but it doesn't store actual data
	GLuint triangle_settings;
	glGenVertexArrays(1, &triangle_settings);
	glBindVertexArray(triangle_settings);

	// each line = vertex
	// first three values are xyz coordinates and the last three values are RGB colors
	float triangle_data[] = {
        -0.7, -0.5, -0.5, 1.,  0, 0,
         0.5, -0.5, -0.5, 1.,  0, 0,
         0.5,  0.7, -0.5, 1.,  0, 0,
        -0.5, -0.7,    0,  0, 1., 0,
         0.7,  0.5,    0,  0, 1., 0,
        -0.5,  0.5,    0,  0, 1., 0
	};
	// green triangle in the back because clip space is a left handed coordinate system

	// create vertex buffer object (VBO), get a handle to the buffer, load triangle vertices into the buffer
	GLuint triangle_buffer;
	glGenBuffers(1, &triangle_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);
	
	// get a handle to the "vertex_position" input attribute, tell it to read 3 floats at a time
	// for the variable related to vertex_position_attribute, give it three data values
	// data of the form floats, data which shouldn't be normalized, data which comes in chunks of 6
	// take the three data values stating from byte 0 in such a chunk
	GLint vertex_position_attribute = glGetAttribLocation(shader_program, "vertex_position");
	glVertexAttribPointer(vertex_position_attribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(vertex_position_attribute);

	// get a handle to the "color_input" input attribute, tell it to read 3 floats at a time
	GLint color_in_attribute = glGetAttribLocation(shader_program, "color_input");
	glVertexAttribPointer(color_in_attribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(color_in_attribute);
}

void View::render(SDL_Window* window) {
	// clear color and depth buffer, in order the camera might have moved
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render objects from buffer
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// force execution of GL commands in finite time
	glFlush();

	// used with double-buffered OpenGL contexts to swap context
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
