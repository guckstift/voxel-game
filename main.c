#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "shader.h"
#include "buffer.h"

int main(int argc, char **argv)
{
	SDL_Window *window;
	SDL_GLContext gl;
	int running = 1;
	SDL_Event event;
	Shader *shader;
	Buffer *buffer;
	GLint vert_pos;
	GLfloat tria[] = {0,0, 1,0, 0,1};
	GLuint vao;
	
	printf("voxel-game\n");
	
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	window = SDL_CreateWindow(
		"voxel-game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE
	);
	
	gl = SDL_GL_CreateContext(window);
		
	glewInit();
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glClearColor(1, 0, 0, 1);
	
	shader = create_shader_from_files("vert.glsl", "frag.glsl");
	vert_pos = glGetAttribLocation(shader->prog, "vert_pos");
	buffer = create_buffer();
	buffer->data = tria;
	buffer->size = sizeof(tria);
	update_buffer(buffer);
	
	while(running) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_WINDOWEVENT:
					if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
						Sint32 w = event.window.data1;
						Sint32 h = event.window.data2;
						
						glViewport(0, 0, w, h);
					}
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_LEFT:
							break;
						case SDLK_RIGHT:
							break;
						case SDLK_UP:
							break;
						case SDLK_DOWN:
							break;
					}
					
					break;
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shader->prog);
		
		glEnableVertexAttribArray(vert_pos);
		glBindBuffer(GL_ARRAY_BUFFER, buffer->buf);
		glVertexAttribPointer(vert_pos, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DeleteContext(gl);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
