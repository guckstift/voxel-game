#include <math.h>
#include <string.h>
#include "matrix.h"

void identity(Matrix m)
{
	memset(m, 0, sizeof(GLfloat) * 16);
	
	m[0] = 1;
	m[5] = 1;
	m[10] = 1;
	m[15] = 1;
}

void mat_translate(Matrix m, GLfloat x, GLfloat y, GLfloat z)
{
	m[12] += x * m[0] + y * m[4] + z * m[8];
	m[13] += x * m[1] + y * m[5] + z * m[9];
	m[14] += x * m[2] + y * m[6] + z * m[10];
	m[15] += x * m[3] + y * m[7] + z * m[11];
}

void perspective(Matrix m, GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far)
{
	GLfloat fy = 1.0 / tan(fovy / 2);
	GLfloat fx = fy / aspect;
	GLfloat nf = 1.0 / (near - far);
	GLfloat a  = (near + far) * nf;
	GLfloat b  = 2.0 * near * far * nf;
	
	memset(m, 0, sizeof(GLfloat) * 16);
	
	m[0] = fx;
	m[5] = fy;
	m[10] = a;
	m[11] = -1;
	m[14] = b;
}

void mat_rotate_x(Matrix m, GLfloat a)
{
	GLfloat s = sin(a);
	GLfloat c = cos(a);
	GLfloat a10 = m[4], a11 = m[5], a12 = m[6],  a13 = m[7];
	GLfloat a20 = m[8], a21 = m[9], a22 = m[10], a23 = m[11];
	
	m[4]  =  c * a10 + s * a20;
	m[5]  =  c * a11 + s * a21;
	m[6]  =  c * a12 + s * a22;
	m[7]  =  c * a13 + s * a23;
	m[8]  = -s * a10 + c * a20;
	m[9]  = -s * a11 + c * a21;
	m[10] = -s * a12 + c * a22;
	m[11] = -s * a13 + c * a23;
}

void mat_rotate_y(Matrix m, GLfloat a)
{
	GLfloat s = sin(a);
	GLfloat c = cos(a);
	GLfloat a00 = m[0], a01 = m[1], a02 = m[2],  a03 = m[3];
	GLfloat a20 = m[8], a21 = m[9], a22 = m[10], a23 = m[11];
	
	m[0]  =  c * a00 + s * a20;
	m[1]  =  c * a01 + s * a21;
	m[2]  =  c * a02 + s * a22;
	m[3]  =  c * a03 + s * a23;
	m[8]  = -s * a00 + c * a20;
	m[9]  = -s * a01 + c * a21;
	m[10] = -s * a02 + c * a22;
	m[11] = -s * a03 + c * a23;
}

void mat_rotate_z(Matrix m, GLfloat a)
{
	GLfloat s = sin(a);
	GLfloat c = cos(a);
	GLfloat a00 = m[0], a01 = m[1], a02 = m[2], a03 = m[3];
	GLfloat a10 = m[4], a11 = m[5], a12 = m[6], a13 = m[7];
	
	m[0] =  c * a00 + s * a10;
	m[1] =  c * a01 + s * a11;
	m[2] =  c * a02 + s * a12;
	m[3] =  c * a03 + s * a13;
	m[4] = -s * a00 + c * a10;
	m[5] = -s * a01 + c * a11;
	m[6] = -s * a02 + c * a12;
	m[7] = -s * a03 + c * a13;
}
