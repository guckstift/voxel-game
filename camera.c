#include "camera.h"
#include "memory.h"
#include "mathx.h"

Camera *create_camera()
{
	Camera *cam = create(Camera);
	
	init_object(&cam->obj);
	
	cam->fovy = 90;
	cam->aspect = 800.0 / 600.0;
	cam->near = 0.1;
	cam->far = 1000.0;
	
	return cam;
}

void update_camera(Camera *cam)
{
	update_object(&cam->obj);
	
	perspective(cam->proj, radians(cam->fovy), cam->aspect, cam->near, cam->far);
	
	identity(cam->view);
	mat_rotate_x(cam->view, -radians(cam->obj.rx));
	mat_rotate_z(cam->view, -radians(cam->obj.rz));
	mat_translate(cam->view, -cam->obj.pos[0], -cam->obj.pos[1], -cam->obj.pos[2]);
}
