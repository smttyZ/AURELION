#pragma once

#include "Mat4.h"
#include "Vector3.h"

/**
 * @file MatrixTransform.h
 * @brief Utility functions related to matrix transformations.
 * 
 * These functions return pre-filled mat4s for common 3D operations like
 * perspective projection and camera orientation. Basically, they do the math
 * so you don’t have to cry over frustum diagrams.
 */

 /**
 * Creates a perspective projection matrix.
 * 
 * @param fovRadians Field of view in radians.
 * @param aspect Aspect ratio (width / height).
 * @param near Near clipping plane.
 * @param far Far clipping plane.
 * @return A mat4 representing the perspective projection.
 */
mat4 perspective(float fovRadians, float aspect, float near, float far);

/**
 * Creates a view matrix using the camera's position and orientation.
 * 
 * @param eye Position of the camera.
 * @param center Point the camera is looking at.
 * @param up Up direction (usually vec3(0, 1, 0)).
 * @return A mat4 representing the view transformation.
 */
mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up);

