#include <string.h>
#include "shader.h"
#include "memory.h"
#include "file.h"
#include "error.h"

static Shader *cur = 0;

Shader *create_shader(const char *vert_src, const char *frag_src)
{
	Shader *shader = create(Shader);
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar **vert_src_ptr = &vert_src;
	const GLchar **frag_src_ptr = &frag_src;
	GLint vert_src_len[1];
	GLint frag_src_len[1];
	GLint status;
	
	vert_src_len[0] = strlen(vert_src);
	frag_src_len[0] = strlen(frag_src);
	
	shader->prog = glCreateProgram();
	
	glShaderSource(vert, 1, vert_src_ptr, vert_src_len);
	glShaderSource(frag, 1, frag_src_ptr, frag_src_len);
	
	glCompileShader(vert);
	glCompileShader(frag);
	
	glAttachShader(shader->prog, vert);
	glAttachShader(shader->prog, frag);
	
	glLinkProgram(shader->prog);
	
	glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
	
	if(status == GL_FALSE) {
		GLchar *info_log;
		
		glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &status);
		info_log = alloc(status);
		glGetShaderInfoLog(vert, status, 0, info_log);
		error("could not compile vertex shader code:\n%s", info_log);
	}
	
	glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
	
	if(status == GL_FALSE) {
		GLchar *info_log;
		
		glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &status);
		info_log = alloc(status);
		glGetShaderInfoLog(frag, status, 0, info_log);
		error("could not compile fragment shader code:\n%s", info_log);
	}
	
	glGetProgramiv(shader->prog, GL_LINK_STATUS, &status);
	
	if(status == GL_FALSE) {
		GLchar *info_log;
		
		glGetProgramiv(shader->prog, GL_INFO_LOG_LENGTH, &status);
		info_log = alloc(status);
		glGetProgramInfoLog(shader->prog, status, 0, info_log);
		error("could not link shader program:\n%s", info_log);
	}
	
	return shader;
}

Shader *create_shader_from_files(const char *vert_file_name, const char *frag_file_name)
{
	char *vert_src = read_file(vert_file_name);
	char *frag_src = read_file(frag_file_name);
	Shader *shader = create_shader(vert_src, frag_src);
	
	dealloc(vert_src);
	dealloc(frag_src);
	
	return shader;
}

void use_shader(Shader *shader)
{
	cur = shader;
	glUseProgram(cur->prog);
}

void assign_attrib(const GLchar *name, Buffer *buf, GLint size, GLsizei stride, const void *offset)
{
	GLint loca = glGetAttribLocation(cur->prog, name);
	
	glEnableVertexAttribArray(loca);
	glBindBuffer(GL_ARRAY_BUFFER, buf->buf);
	glVertexAttribPointer(loca, size, GL_FLOAT, GL_FALSE, stride, offset);
}

void assign_matrix(const GLchar *name, const GLfloat *mat)
{
	GLint loca = glGetUniformLocation(cur->prog, name);
	
	glUniformMatrix4fv(loca, 1, GL_FALSE, mat);
}
