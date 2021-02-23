#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>

typedef GLuint Buffer;

Buffer create_buffer(void *data, GLsizeiptr size);
void update_buffer(Buffer buf, void *data, GLsizeiptr size);

#endif
