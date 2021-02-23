#include <string.h>
#include <math.h>
#include "vector.h"

void init_vector(Vector v)
{
	memset(v, 0, sizeof(GLfloat) * 3);
}

void set_vector(Vector v, GLfloat x, GLfloat y, GLfloat z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

void copy_vec(Vector dest, Vector src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}

void vec_scale(Vector v, GLfloat s)
{
	v[0] *= s;
	v[1] *= s;
	v[2] *= s;
}

void vec_add(Vector v, Vector o)
{
	v[0] += o[0];
	v[1] += o[1];
	v[2] += o[2];
}

void vec_rotate_x(Vector v, GLfloat a)
{
	GLfloat s = sin(a);
	GLfloat c = cos(a);
	GLfloat y = v[1];
	GLfloat z = v[2];
	v[1] = y * c - z * s;
	v[2] = y * s + z * c;
}

void vec_rotate_z(Vector v, GLfloat a)
{
	GLfloat s = sin(a);
	GLfloat c = cos(a);
	GLfloat x = v[0];
	GLfloat y = v[1];
	v[0] = x * c - y * s;
	v[1] = x * s + y * c;
}
