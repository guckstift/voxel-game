#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include "object.h"
#include "matrix.h"

typedef struct {
	Object obj;
	GLfloat fovy;
	GLfloat aspect;
	GLfloat near;
	GLfloat far;
	Matrix proj;
	Matrix view;
} Camera;

Camera *create_camera();
void update_camera(Camera *cam);

#endif
