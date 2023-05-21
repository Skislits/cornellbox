#include "modelgeometry.h"

Rectangle::Rectangle(vector<vec3> rectangle_corners, vec3 RGB_color) :
    rectangle_corners(rectangle_corners), RGB_color(RGB_color) {}

const vec3& Rectangle::operator[](const size_t& index) const {
    return rectangle_corners[index];
}

Block::Block(vector<Rectangle> block_sides) :block_sides(block_sides) {}
