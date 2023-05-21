#include "camera.h"

Camera::Camera() {}

void Camera::updateViewMatrix() {
	// pitch-then-yaw rotation
	direction = vec3(-sin(yaw) * cos(pitch), sin(pitch), -cos(pitch) * cos(yaw));
	right = vec3(cos(yaw), 0, -sin(yaw));
	up = cross(right, direction);

	view_matrix = lookAt(position, position + direction, up);
}
