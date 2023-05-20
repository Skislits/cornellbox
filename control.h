#ifndef CONTROL
#define CONTROL

#include "SDL.h"
#include "model.h"

class Control {
private:
	Model& model;
	const Uint8* key_state;
public:
	void handleInput();
	Control(Model& model);
};

#endif 
