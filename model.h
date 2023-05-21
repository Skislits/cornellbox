#ifndef MODEL
#define MODEL

#include <vector>
#include "modelgeometry.h"

class Model {
public:
	Rectangle scene_floor;
	Rectangle scene_ceiling;
	Rectangle scene_back_wall;
	Rectangle scene_right_wall;
	Rectangle scene_left_wall;
	Block short_block;
	Block tall_block;

	Model();
};

#endif
