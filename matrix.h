#ifndef MATRIX_H
#define MATRIX_H

#include <GL/glew.h>

typedef GLfloat Matrix[16];

void identity(Matrix mat);
void mat_translate(Matrix m, GLfloat x, GLfloat y, GLfloat z);
void perspective(Matrix m, GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far);
void mat_rotate_x(Matrix m, GLfloat a);
void mat_rotate_y(Matrix m, GLfloat a);
void mat_rotate_z(Matrix m, GLfloat a);

#endif
