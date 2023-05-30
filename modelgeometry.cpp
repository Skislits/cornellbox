#include "modelgeometry.h"

Rectangle::Rectangle(vector<vec3> rectangle_corners, vec3 RGB_color) :
    rectangle_corners(rectangle_corners), RGB_color(RGB_color) {}

const vec3& Rectangle::operator[](const size_t& index) const {
    return rectangle_corners[index];
}

void Rectangle::moveToPoint(vec3 first_corner) {
    // move each point on same vector
    vec3 direction = first_corner - this->rectangle_corners[0];
    for (int vertex_num = 0; vertex_num < 4; vertex_num++) {
        this->rectangle_corners[vertex_num] += direction;
    }
}

Block::Block(vector<Rectangle> block_sides) :block_sides(block_sides) {}
