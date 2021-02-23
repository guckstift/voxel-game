#include "object.h"
#include "mathx.h"

void init_object(Object *obj)
{
	init_vector(obj->pos);
	init_vector(obj->vel);
	set_vector(obj->rightward, 1, 0, 0);
	set_vector(obj->forward, 0, 1, 0);
	set_vector(obj->upward, 0, 0, 1);
}

void update_object(Object *obj)
{
	set_vector(obj->rightward, 1, 0, 0);
	vec_rotate_z(obj->rightward, radians(obj->rz));
	
	set_vector(obj->forward, 0, 1, 0);
	vec_rotate_z(obj->forward, radians(obj->rz));
}

void move_rightward(Object *obj, GLfloat delta)
{
	move_object(obj, obj->rightward, +delta);
}

void move_leftward(Object *obj, GLfloat delta)
{
	move_object(obj, obj->rightward, -delta);
}

void move_forward(Object *obj, GLfloat delta)
{
	move_object(obj, obj->forward, +delta);
}

void move_backward(Object *obj, GLfloat delta)
{
	move_object(obj, obj->forward, -delta);
}

void move_upward(Object *obj, GLfloat delta)
{
	move_object(obj, obj->upward, +delta);
}

void move_downward(Object *obj, GLfloat delta)
{
	move_object(obj, obj->upward, -delta);
}

void move_object(Object *obj, Vector vec, GLfloat delta)
{
	Vector deltavec;
	
	copy_vec(deltavec, vec);
	vec_scale(deltavec, delta);
	vec_add(obj->pos, deltavec);
}
