// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include <iostream>

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	// YOUR CODE FOR HW2 HERE
	// Please implement this.  Likely the same as in HW 1.
	float radians = glm::radians(degrees);
	float one_minus_cos = 1.0f - cos(radians);
	float x_square = (float)pow(axis.x, 2.0f);
	float y_square = (float)pow(axis.y, 2.0f);
	float z_square = (float)pow(axis.z, 2.0f);
	float xy = axis.x * axis.y;
	float xz = axis.x * axis.z;
	float yz = axis.y * axis.z;
	mat3 unchanged_cmp(cos(radians), 0.0, 0.0, 0.0, cos(radians), 0.0, 0.0, 0.0, cos(radians));
	mat3 along_cmp = one_minus_cos * mat3(x_square, xy, xz, xy, y_square, yz, xz, yz, z_square);
	mat3 rotate_cmp(0.0, -sin(radians) * axis.z, sin(radians) * axis.y, sin(radians) * axis.z, 0.0, -sin(radians) * axis.x, -sin(radians) * axis.y, sin(radians) * axis.x, 0.0);
	mat3 rotation_matrix = unchanged_cmp + along_cmp + rotate_cmp;
	rotation_matrix = glm::transpose(rotation_matrix);
	return rotation_matrix;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
	// YOUR CODE FOR HW2 HERE
	// Likely the same as in HW 1.
	vec3 axis = glm::normalize(up);
	mat3 rotation_matrix = Transform::rotate(degrees, axis);
	eye = rotation_matrix * eye;
	up = rotation_matrix * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
	// YOUR CODE FOR HW2 HERE 
	// Likely the same as in HW 1.
	vec3 axis = glm::normalize(glm::cross(up, -eye));
	mat3 rotation_matrix = Transform::rotate(degrees, axis);
	eye = rotation_matrix * eye;
	up = rotation_matrix * up;
}

mat4 Transform::lookAt(const vec3& eye, const vec3& center, const vec3& up)
{
	// YOUR CODE FOR HW2 HERE
	// Likely the same as in HW 1.
	vec3 w = glm::normalize(eye + center);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	mat4 glu_look_at_matrix(u.x, u.y, u.z, -glm::dot(u, eye + center), v.x, v.y, v.z, -glm::dot(v, eye + center), w.x, w.y, w.z, -glm::dot(w, eye + center), 0.0, 0.0, 0.0, 1.0f);
	glu_look_at_matrix = glm::transpose(glu_look_at_matrix);
	return glu_look_at_matrix;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	// YOUR CODE FOR HW2 HERE
	// New, to implement the perspective transform as well.  
	float theta = fovy / 2;
	float d = 1 / tan(glm::radians(theta));
	float A = -(zFar + zNear) / (zFar - zNear);
	float B = -2 * zFar * zNear / (zFar - zNear);
	mat4 gluPerspective(d / aspect, 0.0, 0.0, 0.0, 0.0, d, 0.0, 0.0, 0.0, 0.0, A, B, 0.0, 0.0, -1.0f, 0.0);
	gluPerspective = glm::transpose(gluPerspective);
	return gluPerspective;
}

mat4 Transform::scale(const float& sx, const float& sy, const float& sz)
{
	// YOUR CODE FOR HW2 HERE
	// Implement scaling
	mat4 scaling_matrix(sx, 0.0, 0.0, 0.0, 0.0, sy, 0.0, 0.0, 0.0, 0.0, sz, 0.0, 0.0, 0.0, 0.0, 1.0f);
	scaling_matrix = glm::transpose(scaling_matrix);
	return scaling_matrix;
}

mat4 Transform::translate(const float& tx, const float& ty, const float& tz)
{
	// YOUR CODE FOR HW2 HERE
	// Implement translation
	mat4 translation_matrix(1.0f, 0.0, 0.0, tx, 0.0, 1.0f, 0.0, ty, 0.0, 0.0, 1.0, tz, 0.0, 0.0, 0.0, 1.0f);
	translation_matrix = glm::transpose(translation_matrix);
	return translation_matrix;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3& up, const vec3& zvec)
{
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
