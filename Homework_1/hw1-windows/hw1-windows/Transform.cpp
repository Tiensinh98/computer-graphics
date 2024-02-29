// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE

	// You will change this return call
	double radians = double(degrees * pi / 180);
	double one_minus_cos = double(1 - cos(radians));
	double x_square = double(pow(axis.x, 2));
	double y_square = double(pow(axis.y, 2));
	double z_square = double(pow(axis.z, 2));
	double xy = double(axis.x) * double(axis.y);
	double xz = double(axis.x) * double(axis.z);
	double yz = double(axis.y) * double(axis.z);
	mat3 unchanged_cmp(cos(radians), 0, 0, 0, cos(radians), 0, 0, 0, cos(radians));
	mat3 along_cmp(one_minus_cos * x_square, one_minus_cos * xy, one_minus_cos * xz, one_minus_cos * xy, one_minus_cos * y_square, one_minus_cos * yz, one_minus_cos * xz, one_minus_cos * yz, one_minus_cos * z_square);
	mat3 rotate_cmp(0, -sin(radians) * axis.z, sin(radians) * axis.y, sin(radians) * axis.z, 0, -sin(radians) * axis.x, -sin(radians) * axis.y, sin(radians) * axis.x, 0);
	mat3 rotation_matrix = unchanged_cmp + along_cmp + rotate_cmp;
	rotation_matrix = glm::transpose(rotation_matrix);
	return rotation_matrix;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	vec3 axis = glm::normalize(up);
	mat3 rotation_matrix = Transform::rotate(degrees, axis);
	eye = rotation_matrix * eye;
	up = rotation_matrix * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	vec3 axis = glm::normalize(glm::cross(up, -eye));
	mat3 rotation_matrix = Transform::rotate(degrees, axis);
	eye = rotation_matrix * eye;
	up = rotation_matrix * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE

	// You will change this return call
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	mat4 glu_look_at_matrix(u.x, u.y, u.z, -glm::dot(u, eye), v.x, v.y, v.z, -glm::dot(v, eye), w.x, w.y, w.z, -glm::dot(w, eye), 0, 0, 0, 1);
	glu_look_at_matrix = glm::transpose(glu_look_at_matrix);
	return glu_look_at_matrix;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}