#ifndef MEMORY_H
#define MEMORY_H

#define create(type) ((type*)alloc(sizeof(type)))

void *alloc(int size);
void dealloc(void *ptr);

#endif
