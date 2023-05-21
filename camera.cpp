#include "camera.h"

Camera::Camera() {}

void Camera::updateViewMatrix() {
	view_matrix = lookAt(position, position + direction, up);
}
