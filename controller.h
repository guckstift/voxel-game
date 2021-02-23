#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>
#include "camera.h"

typedef struct {
	Camera *cam;
	Uint8 keymap[256];
	Uint8 key_lshift;
	Uint8 locked;
} Controller;

Controller *create_controller(Camera *cam);
int handle_event(Controller *con, SDL_Event *event);
void update_controller(Controller *con, GLfloat delta);

#endif
