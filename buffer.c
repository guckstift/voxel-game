#include "buffer.h"
#include "memory.h"

Buffer create_buffer(void *data, GLsizeiptr size)
{
	Buffer buf;
	glGenBuffers(1, &buf);
	
	if(data) {
		update_buffer(buf, data, size);
	}
	
	return buf;
}

void update_buffer(Buffer buf, void *data, GLsizeiptr size)
{
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
