#ifndef MATRIX_H
#define MATRIX_H

#include <GL/glew.h>

void identity(GLfloat *mat);
void translate(GLfloat *m, GLfloat x, GLfloat y, GLfloat z);
void perspective(GLfloat *mat, GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far);

#endif
