#ifndef MODELGEOMETRY
#define MODELGEOMETRY

#include <vector>
#include "glm.hpp"

using glm::vec3;
using std::vector;

class Rectangle {
public:
    vec3 RGB_color;
    vector<vec3> rectangle_corners;
    Rectangle(vector<vec3> rectangle_corners, vec3 RGB_color);
    const vec3& operator[](const size_t& index) const;
};

class Block {
public:
    vector<Rectangle> block_sides;
    Block(vector<Rectangle> block_sides);
};

#endif
