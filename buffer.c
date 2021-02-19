#include "buffer.h"
#include "memory.h"

Buffer *create_buffer()
{
	Buffer *buffer = create(Buffer);
	
	glGenBuffers(1, &buffer->buf);
	buffer->data = 0;
	buffer->size = 0;
	
	return buffer;
}

void update_buffer(Buffer *buf)
{
	glBindBuffer(GL_ARRAY_BUFFER, buf->buf);
	glBufferData(GL_ARRAY_BUFFER, buf->size, buf->data, GL_STATIC_DRAW);
}
