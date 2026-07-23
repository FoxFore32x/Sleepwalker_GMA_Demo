// Object: oNXCon

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

std::vector<Object> vector_oNXCon;
static int oNXCon_call_index = 0;
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
void oNXCon_config() {
sprite_index = -1;
visible = 0;
solid = 0;
persistent = 1;
}

void oNXCon_create() {

/// @description Initialize Controller Applet

global.nxgp = -1;

/*var styles = switch_controller_handheld | switch_controller_pro_controller;
//accept only physically connected joycons and a pro controller.

switch_controller_set_supported_styles(styles);
switch_controller_joycon_set_holdtype(switch_controller_joycon_holdtype_horizontal);

// Ensure that the handheld joycon style requires both joy-cons connected to be active.
switch_controller_set_handheld_activation_mode(
	switch_controller_handheld_activation_dual
);

switch_controller_support_set_defaults();
switch_controller_support_set_singleplayer_only(true);
switch_controller_support_show(); //show the applet

if (os_version != os_switch && os_version != os_switch2) {
	global.nxgp = 0;
}*/


}

void oNXCon_step() {

//draw_boundbox();
}
void oNXCon_draw() {
draw_self();
}

#undef x
#undef y
#undef image_xscale
#undef image_yscale
#undef id
void oNXCon_precreate(float NEWX, float NEWY, float NEWXSCALE, float NEWYSCALE, float NEWID) {
Object inst;
inst.GetVar(varId_x) = NEWX;
inst.GetVar(varId_y) = NEWY;
inst.GetVar(varId_image_xscale) = NEWXSCALE;
inst.GetVar(varId_image_yscale) = NEWYSCALE;
inst.GetVar(varId_id) = NEWID;
vector_oNXCon.push_back(inst);
self = &vector_oNXCon.back();
oNXCon_config();
oNXCon_create();
}

void oNXCon_reset_frame() {
	oNXCon_call_index = 0;
}

void oNXCon_runevents(float NEWX, float NEWY, float NEWXSCALE, float NEWYSCALE, float NEWID) {
	//printf("RUNNING OBJECT: oNXCon\n");
	bool found = false;
	for(size_t j = 0; j < vector_oNXCon.size(); j++){
		if(vector_oNXCon[j].GetVar(varId_id) == NEWID){
			found = true;
			break;
		}
	}
	if(!found)
		oNXCon_precreate(NEWX, NEWY, NEWXSCALE, NEWYSCALE, NEWID);
	for(size_t j = 0; j < vector_oNXCon.size(); j++){
		self = &vector_oNXCon[j];
		CurrentObjectRunning = self;
		oNXCon_step();
		oNXCon_draw();

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

