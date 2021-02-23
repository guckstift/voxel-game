#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"

typedef struct {
	Vector pos;
	Vector vel;
	GLfloat rx;
	GLfloat rz;
	Vector rightward;
	Vector forward;
	Vector upward;
} Object;

void init_object(Object *obj);
void update_object(Object *obj);
void move_rightward(Object *obj, GLfloat delta);
void move_leftward(Object *obj, GLfloat delta);
void move_forward(Object *obj, GLfloat delta);
void move_backward(Object *obj, GLfloat delta);
void move_upward(Object *obj, GLfloat delta);
void move_downward(Object *obj, GLfloat delta);
void move_object(Object *obj, Vector vec, GLfloat delta);

#endif
