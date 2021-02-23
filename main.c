#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "shader.h"
#include "buffer.h"
#include "matrix.h"
#include "mathx.h"
#include "camera.h"
#include "controller.h"

static SDL_Window *window = 0;
static SDL_GLContext gl;
static GLuint vao;
static Camera *cam;
static Shader shader;
static Buffer buffer;
static Controller *con;

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
	
	SDL_GL_SetSwapInterval(1);
	
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

void on_frame(double delta)
{
	update_controller(con, delta);
	update_camera(cam);
	
	use_shader(shader);
	
	assign_matrix("proj", cam->proj);
	assign_matrix("view", cam->view);
	assign_attrib("vert_pos", buffer, 2, 0, 0);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char **argv)
{
	printf("voxel-game\n");
	init_video();
	
	shader = create_shader_from_files("vert.glsl", "frag.glsl");
	GLfloat tria[] = {0,0, 1,0, 0,1};
	buffer = create_buffer(tria, sizeof(tria));
	
	cam = create_camera();
	cam->obj.pos[2] = 2;
	update_camera(cam);
	
	con = create_controller(cam);
	
	int running = 1;
	SDL_Event event;
	Uint64 freq = SDL_GetPerformanceFrequency();
	double last = 0, now = 0, delta = 0;
	
	while(running) {
		now = SDL_GetPerformanceCounter() / (double)freq;
		
		if(last) {
			delta = now - last;
		}
		else {
			delta = 0;
		}
		
		last = now;
		
		while(SDL_PollEvent(&event)) {
			if(!handle_event(con, &event)) {
				running = 0;
				break;
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		on_frame(delta);
		
		SDL_GL_SwapWindow(window);
	}
	
	cleanup_video();
	
	return 0;
}
