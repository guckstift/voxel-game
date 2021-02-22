#include <math.h>
#include <string.h>
#include "matrix.h"

void identity(GLfloat *mat)
{
	memset(mat, 0, sizeof(GLfloat) * 16);
	
	mat[0] = 1;
	mat[5] = 1;
	mat[10] = 1;
	mat[15] = 1;
}

void translate(GLfloat *m, GLfloat x, GLfloat y, GLfloat z)
{
	m[12] += x * m[0] + y * m[4] + z * m[8];
	m[13] += x * m[1] + y * m[5] + z * m[9];
	m[14] += x * m[2] + y * m[6] + z * m[10];
	m[15] += x * m[3] + y * m[7] + z * m[11];
}

void perspective(GLfloat *mat, GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far)
{
	GLfloat fy = 1.0 / tan(fovy / 2);
	GLfloat fx = fy / aspect;
	GLfloat nf = 1.0 / (near - far);
	GLfloat a  = (near + far) * nf;
	GLfloat b  = 2.0 * near * far * nf;
	
	memset(mat, 0, sizeof(GLfloat) * 16);
	
	mat[0] = fx;
	mat[5] = fy;
	mat[10] = a;
	mat[11] = -1;
	mat[14] = b;
}
