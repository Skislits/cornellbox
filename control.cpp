#include "control.h"

Control::Control(Model& model, View& view) :model(model), view(view) {
	key_state = SDL_GetKeyboardState(nullptr);
	// SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Control::handleInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);
		//if (event.type == SDL_MOUSEMOTION) {
		// 	view.camera.pitch -= event.motion.yrel * 0.01f;
		//	view.camera.yaw -= event.motion.xrel * 0.01f;
		//}
	}

	if (key_state[SDL_SCANCODE_W]) { view.camera.position += view.camera.direction; }
	if (key_state[SDL_SCANCODE_A]) { view.camera.position -= view.camera.right; }
	if (key_state[SDL_SCANCODE_S]) { view.camera.position -= view.camera.direction; }
	if (key_state[SDL_SCANCODE_D]) { view.camera.position += view.camera.right; }

	if (key_state[SDL_SCANCODE_UP]) { view.light_position[2] += 10.0f; }
	if (key_state[SDL_SCANCODE_DOWN]) { view.light_position[2] -= 10.0f; }
	if (key_state[SDL_SCANCODE_LEFT]) { view.light_position[0] += 10.0f; }
	if (key_state[SDL_SCANCODE_RIGHT]) { view.light_position[0] -= 10.0f; }
}
