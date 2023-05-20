#include "control.h"

Control::Control(Model& model) :model(model) {
	key_state = SDL_GetKeyboardState(nullptr);
}

void Control::handleInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {}
}
