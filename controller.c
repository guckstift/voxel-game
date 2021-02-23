#include "controller.h"
#include "memory.h"

Controller *create_controller(Camera *cam)
{
	Controller *con = create(Controller);
	
	con->cam = cam;
	memset(con->keymap, 0, 256);
	con->key_lshift = 0;
	con->locked = 0;
	
	return con;
}

void on_resize(Controller *con, Sint32 w, Sint32 h)
{
	glViewport(0, 0, w, h);
	con->cam->aspect = (float) w / h;
}

void on_keydown(Controller *con, SDL_Keycode key)
{
	//printf("%i\n", key);
	
	if(key >= 0 && key < 256) {
		con->keymap[key] = 1;
	}
	else if(key == SDLK_LSHIFT) {
		con->key_lshift = 1;
	}
	
	if(key == SDLK_ESCAPE) {
		SDL_SetRelativeMouseMode(0);
		con->locked = 0;
	}
}

void on_keyup(Controller *con, SDL_Keycode key)
{
	if(key >= 0 && key < 256) {
		con->keymap[key] = 0;
	}
	else if(key == SDLK_LSHIFT) {
		con->key_lshift = 0;
	}
}

void on_mousedown(Controller *con, Uint8 button)
{
	if(button == SDL_BUTTON_LEFT) {
		SDL_SetRelativeMouseMode(1);
		con->locked = 1;
	}
}

void on_mouseup(Controller *con, Uint8 button)
{
	if(button == SDL_BUTTON_LEFT) {
	}
}

void on_mousemove(Controller *con, Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel)
{
	//printf("%i %i %i %i\n", x, y, xrel, yrel);
	
	if(con->locked) {
		con->cam->obj.rx -= yrel;
		con->cam->obj.rz -= xrel;
	}
}

int handle_event(Controller *con, SDL_Event *event)
{
	switch(event->type) {
		case SDL_QUIT:
			return 0;
		case SDL_WINDOWEVENT:
			if(event->window.event == SDL_WINDOWEVENT_RESIZED) {
				Sint32 w = event->window.data1;
				Sint32 h = event->window.data2;
				on_resize(con, w, h);
			}
			break;
		case SDL_KEYDOWN:
			on_keydown(con, event->key.keysym.sym);
			break;
		case SDL_KEYUP:
			on_keyup(con, event->key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			on_mousedown(con, event->button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			on_mouseup(con, event->button.button);
			break;
		case SDL_MOUSEMOTION:
			on_mousemove(con, event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
			break;
	}
	
	return 1;
}

void update_controller(Controller *con, GLfloat delta)
{
	if(con->keymap[SDLK_w]) {
		move_forward(&con->cam->obj, delta);
	}
	
	if(con->keymap[SDLK_s]) {
		move_backward(&con->cam->obj, delta);
	}
	
	if(con->keymap[SDLK_d]) {
		move_rightward(&con->cam->obj, delta);
	}
	
	if(con->keymap[SDLK_a]) {
		move_leftward(&con->cam->obj, delta);
	}
	
	if(con->keymap[SDLK_SPACE]) {
		move_upward(&con->cam->obj, delta);
	}
	
	if(con->key_lshift) {
		move_downward(&con->cam->obj, delta);
	}
}
