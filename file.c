#include <stdio.h>
#include "file.h"
#include "memory.h"
#include "error.h"

char *read_file(const char *file_name)
{
	FILE *fs = fopen(file_name, "rb");	
	
	if(fs == 0) {
		error("could not open file %s", file_name);
	}
	
	fseek(fs, 0, SEEK_END);
	
	long len = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	
	char *data = alloc(len + 1);
	data[len] = 0;
	fread(data, 1, len, fs);
	fclose(fs);
	
	return data;
}
