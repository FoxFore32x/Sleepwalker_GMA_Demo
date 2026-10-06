// Object: orpgWall

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

ObjectType vector_orpgWall;
static int orpgWall_call_index = 0;
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
void orpgWall_config() {
sprite_index = sWall;
visible = 1;
solid = 0;
persistent = 0;
}

void orpgWall_create() {

}

void orpgWall_step() {

//draw_boundbox();
}
void orpgWall_draw() {
draw_self();
}

#undef x
#undef y
#undef image_xscale
#undef image_yscale
#undef id
void orpgWall_precreate(float NEWX, float NEWY, float NEWXSCALE, float NEWYSCALE, float NEWID) {
Object inst;
inst.GetVar(varId_x) = NEWX;
inst.GetVar(varId_y) = NEWY;
inst.GetVar(varId_image_xscale) = NEWXSCALE;
inst.GetVar(varId_image_yscale) = NEWYSCALE;
inst.GetVar(varId_id) = NEWID;
vector_orpgWall.instances.push_back(inst);
self = &vector_orpgWall.instances.back();
orpgWall_config();
orpgWall_create();
}

void orpgWall_reset_frame() {
	orpgWall_call_index = 0;
}

void orpgWall_runevents(float NEWX, float NEWY, float NEWXSCALE, float NEWYSCALE, float NEWID, bool VISIBLE) {
	//printf("RUNNING OBJECT: orpgWall\n");
	bool found = false;
	for(size_t j = 0; j < vector_orpgWall.instances.size(); j++){
		if(vector_orpgWall.instances[j].GetVar(varId_id) == NEWID){
			found = true;
			break;
		}
	}
	if(!found)
		orpgWall_precreate(NEWX, NEWY, NEWXSCALE, NEWYSCALE, NEWID);
	for(size_t j = 0; j < vector_orpgWall.instances.size(); j++){
		self = &vector_orpgWall.instances[j];
		CurrentObjectRunning = self;
		orpgWall_step();
		if(VISIBLE) orpgWall_draw();

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

