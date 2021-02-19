#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>

typedef struct {
	GLuint buf;
	void *data;
	GLsizeiptr size;
} Buffer;

Buffer *create_buffer();
void update_buffer(Buffer *buf);

#endif
