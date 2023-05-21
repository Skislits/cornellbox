#ifndef CAMERA
#define CAMERA

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

using namespace glm;

class Camera {
	float field_of_view = 1.57f;
	float aspect_ratio = 4.f / 3.f;
	float near_plane = 30.f;
	float far_plane = 3000.f;
public:
	mat4 view_matrix = lookAt(position, position + direction, up);
	mat4 projection_matrix = perspective(field_of_view, aspect_ratio, near_plane, far_plane);

	vec3 position = vec3(278, 273, -800);
	vec3 direction = vec3(0, 0, -1);
	vec3 right = vec3(1, 0, 0);
	vec3 up = vec3(0, 1, 0);

	float yaw = 3.14f;
	float pitch = 0;

	Camera();

	void updateViewMatrix();
};
#endif
