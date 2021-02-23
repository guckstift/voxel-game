#ifndef VECTOR_H
#define VECTOR_H

#include <GL/glew.h>

typedef GLfloat Vector[3];

void init_vector(Vector v);
void set_vector(Vector v, GLfloat x, GLfloat y, GLfloat z);
void copy_vec(Vector dest, Vector src);
void vec_scale(Vector v, GLfloat s);
void vec_add(Vector v, Vector o);
void vec_rotate_x(Vector v, GLfloat a);
void vec_rotate_z(Vector v, GLfloat a);

#endif
