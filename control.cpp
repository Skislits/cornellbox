#include "control.h"

Control::Control(Model& model, View& view) :model(model), view(view) {
	key_state = SDL_GetKeyboardState(nullptr);
}

void Control::handleInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {}

	if (key_state[SDL_SCANCODE_W]) { view.camera.position += view.camera.direction; }
	if (key_state[SDL_SCANCODE_A]) { view.camera.position -= view.camera.right; }
	if (key_state[SDL_SCANCODE_S]) { view.camera.position -= view.camera.direction; }
	if (key_state[SDL_SCANCODE_D]) { view.camera.position += view.camera.right; }
}
