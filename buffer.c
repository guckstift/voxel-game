#include "buffer.h"
#include "memory.h"

Buffer *create_buffer(void *data, GLsizeiptr size)
{
	Buffer *buffer = create(Buffer);
	
	glGenBuffers(1, &buffer->buf);
	buffer->data = data;
	buffer->size = size;
	update_buffer(buffer);
	
	return buffer;
}

void update_buffer(Buffer *buf)
{
	glBindBuffer(GL_ARRAY_BUFFER, buf->buf);
	glBufferData(GL_ARRAY_BUFFER, buf->size, buf->data, GL_STATIC_DRAW);
}
