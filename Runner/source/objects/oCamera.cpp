// Object: oCamera

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../helpers/asset_toid.h"
#include "../gm_funcs/drawing.h"
#include "../gm_funcs/input.h"
#include "../gm_funcs/input.h"
#include "../gm_funcs/misc.h"
#include "../gm_funcs/collision.h"
#include "../gm_funcs/audio.h"
#include "../gm_funcs/filesystem.h"
#include "../custom_funcs/customfuncs.h"
#include "../variable_handler.h"
#include "../helpers/get_spriteinfo.h"
#include "../helpers/asset_toid.h"
#include <variant>
#include <vector>

#include <string>

#undef orpgPlayer

#define orpgPlayer vector_orpgPlayer

ObjectType vector_oCamera;
static int oCamera_call_index = 0;
static int objectid_collided = 0;
#define x GetVar(varId_x, *self)
#define y GetVar(varId_y, *self)
#define sprite_index GetVar(varId_sprite_index, *self)
#define image_xscale GetVar(varId_image_xscale, *self)
#define image_yscale GetVar(varId_image_yscale, *self)
#define sprite_xoffset GetVar(varId_sprite_xoffset, *self)
#define sprite_yoffset GetVar(varId_sprite_yoffset, *self)
#define image_index GetVar(varId_image_index, *self)
#define alarm GetVar(varId_alarm, *self)
#define id GetVar(varId_id, *self)
#define visible GetVar(varId_visible, *self)
#define solid GetVar(varId_solid, *self)
#define persistent GetVar(varId_persistent, *self)
#define depth GetVar(varId_depth, *self)
#define layer GetVar(varId_layer, *self)
#define on_ui_layer GetVar(varId_on_ui_layer, *self)
#define collision_space GetVar(varId_collision_space, *self)
#define direction GetVar(varId_direction, *self)
#define friction GetVar(varId_friction, *self)
#define gravity GetVar(varId_gravity, *self)
#define gravity_direction GetVar(varId_gravity_direction, *self)
#define hspeed GetVar(varId_hspeed, *self)
#define vspeed GetVar(varId_vspeed, *self)
#define speed GetVar(varId_speed, *self)
#define xstart GetVar(varId_xstart, *self)
#define ystart GetVar(varId_ystart, *self)
#define xprevious GetVar(varId_xprevious, *self)
#define yprevious GetVar(varId_yprevious, *self)
#define object_index GetVar(varId_object_index, *self)
#define sprite_width GetVar(varId_sprite_width, *self)
#define sprite_height GetVar(varId_sprite_height, *self)
#define image_alpha GetVar(varId_image_alpha, *self)
#define image_angle GetVar(varId_image_angle, *self)
#define image_blend GetVar(varId_image_blend, *self)
#define image_number GetVar(varId_image_number, *self)
#define image_speed GetVar(varId_image_speed, *self)
#define finalCamX GetVar(varId_finalCamX, *self)
#define finalCamY GetVar(varId_finalCamY, *self)
#define camTrailSpd GetVar(varId_camTrailSpd, *self)
#define view_w GetVar(varId_view_w, *self)
#define view_h GetVar(varId_view_h, *self)
void oCamera_config() {
sprite_index = -1;
visible = 1;
solid = 0;
persistent = 1;
}

void oCamera_create() {

/// Camera smoothing

finalCamX = 0;
finalCamY = 0;
camTrailSpd = 0.25f;

// Internal resolution
view_w = 544;
view_h = 416;

/*orpgPlayer.x = 0;
orpgPlayer.y = 0;*/

// Create camera

// Enable views
view_enabled = true;
view_visible[0] = true;

camera_set_view_size(view_camera[0], view_w, view_h);

// VERY IMPORTANT
// Match viewport to camera size
/*view_set_wport(0, 544);
view_set_hport(0, 416);

// Position viewport
view_set_xport(0, 0);
view_set_yport(0, 0);*/

// Resize application surface
//surface_resize(application_surface, 544, 416);

// Window size
window_set_size(544, 416);

// GUI size
//display_set_gui_size(544, 416);

}

void oCamera_step() {

/// @description Inserte aquí la descripción
// Puede escribir su código en este editor

camera_set_view_size(view_camera[0], view_w, view_h);

//fullscreen toggle
if (keyboard_check_pressed(vk_f8)) {
	window_set_fullscreen(!window_get_fullscreen());
}

if (!instance_exists(orpgPlayer)) {
	exit;
}

var _camWidth = camera_get_view_width(view_camera[0]);
var _camHeigth = camera_get_view_height(view_camera[0]);

var _camX = orpgPlayer.x - _camWidth / 2;
var _camY = orpgPlayer.y - _camHeigth / 2;

//constrain cam
_camX = clamp(_camX, 0, room_width - _camWidth);
_camY = clamp(_camY, 0, room_height - _camHeigth);

//set cam coordenate variables

finalCamX += (_camX - finalCamX) * camTrailSpd;
finalCamY += (_camY - finalCamY) * camTrailSpd;

camera_set_view_pos(view_camera[0], finalCamX, finalCamY);


//draw_boundbox();
}
void oCamera_draw() {
draw_self();
}

#undef x
#undef y
#undef image_xscale
#undef image_yscale
#undef id
void oCamera_precreate(float NEWX, float NEWY, float NEWXSCALE, float NEWYSCALE, float NEWID) {
Object inst;
inst.GetVar(varId_x) = NEWX;
inst.GetVar(varId_y) = NEWY;
inst.GetVar(varId_image_xscale) = NEWXSCALE;
inst.GetVar(varId_image_yscale) = NEWYSCALE;
inst.GetVar(varId_id) = NEWID;
vector_oCamera.instances.push_back(inst);
self = &vector_oCamera.instances.back();
oCamera_config();
oCamera_create();
}

void oCamera_reset_frame() {
	oCamera_call_index = 0;
}

void oCamera_runevents(float NEWX, float NEWY, float NEWXSCALE, float NEWYSCALE, float NEWID) {
	//printf("RUNNING OBJECT: oCamera\n");
	bool found = false;
	for(size_t j = 0; j < vector_oCamera.instances.size(); j++){
		if(vector_oCamera.instances[j].GetVar(varId_id) == NEWID){
			found = true;
			break;
		}
	}
	if(!found)
		oCamera_precreate(NEWX, NEWY, NEWXSCALE, NEWYSCALE, NEWID);
	for(size_t j = 0; j < vector_oCamera.instances.size(); j++){
		self = &vector_oCamera.instances[j];
		CurrentObjectRunning = self;
		oCamera_step();
		oCamera_draw();

	}
	if (SpriteAnimSpeedType[sprite_index] == 0){
		image_index+=SpriteAnimTimer[sprite_index]/fps;
	}
	else
		image_index+=SpriteAnimTimer[sprite_index];
	if (image_index >= SpriteFrameCount[sprite_index]){
		image_index = 0;
	}
}

