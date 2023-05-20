#include "view.h"

View::View(Model& model) : model(model) {}

void View::render(SDL_Window* window) {
	SDL_GL_SwapWindow(window);
}