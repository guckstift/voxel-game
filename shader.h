#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

typedef struct {
	GLuint prog;
} Shader;

Shader *create_shader(const char *vert_src, const char *frag_src);
Shader *create_shader_from_files(const char *vert_file_name, const char *frag_file_name);

#endif
