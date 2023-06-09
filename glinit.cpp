#include "glinit.h"

/*
* Create a window, initialize a GL context and initialize the GLEW library
*/
void init(SDL_Window*& window) {
	SDL_Init(SDL_INIT_EVERYTHING);

	// set attributes before creating a GL context

	// disable deprecated functions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// select version GL 3.0 + GLSL 330
	const char* glsl_version = "#version 330";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // use double buffer

	int x = 20;
	int y = 40;
	int w = 600;
	int h = 600;
	window = SDL_CreateWindow("Cornell Box", x, y, w, h, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		cout << "Failed to create window at startup";
	}
	SDL_GLContext gl_context = SDL_GL_CreateContext(window); 
	SDL_GL_MakeCurrent(window, gl_context); 
	SDL_GL_SetSwapInterval(1); // swap buffer at the monitors rate

	// set all GLEW functions available
	glewExperimental = GL_TRUE;
	glewInit();

	// setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // enable Keyboard Controls

	// setup Dear ImGui style
	ImGui::StyleColorsLight();

	// setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);
}
