#include <stdlib.h>

void *alloc(int size)
{
	return malloc(size);
}

void dealloc(void *ptr)
{
	free(ptr);
}
