#ifndef CONTROL
#define CONTROL

#include "SDL.h"
#include "model.h"
#include "view.h"

class Control {
private:
	Model& model;
	View& view;
	const Uint8* key_state;
public:
	void handleInput();
	Control(Model& model, View& view);
};

#endif 
