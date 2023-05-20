#ifndef VIEW
#define VIEW

#include "SDL.h"
#include "glew.h"
#include "model.h"

class View {
private:
	Model& model;
public:
	View(Model& model);
	void render(SDL_Window* window);
};

#endif
