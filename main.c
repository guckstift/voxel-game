#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "shader.h"
#include "buffer.h"
#include "matrix.h"
#include "mathx.h"

static SDL_Window *window;
static SDL_GLContext gl;
static GLuint vao;

void init_video()
{
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
	
	glClearColor(0, 0, 0, 1);
}

void cleanup_video()
{
	SDL_GL_DeleteContext(gl);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char **argv)
{
	int running = 1;
	SDL_Event event;
	Shader *shader;
	Buffer *buffer;
	GLfloat tria[] = {0,0, 1,0, 0,1};
	GLfloat proj[16];
	GLfloat view[16];
	
	printf("voxel-game\n");
	
	init_video();
	
	shader = create_shader_from_files("vert.glsl", "frag.glsl");
	buffer = create_buffer(tria, sizeof(tria));
	
	perspective(proj, radians(90), 800.0 / 600, 0.1, 1000);
	identity(view);
	translate(view, 0, 0, -2);
	
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
						perspective(proj, 90, (float)w / h, 0.1, 1000);
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
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		use_shader(shader);
		assign_matrix("proj", proj);
		assign_matrix("view", view);
		assign_attrib("vert_pos", buffer, 2, 0, 0);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		SDL_GL_SwapWindow(window);
	}
	
	cleanup_video();
	
	return 0;
}
