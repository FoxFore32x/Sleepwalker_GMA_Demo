// Object: orpgPlayer

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

#undef orpgWall

#define orpgWall vector_orpgWall

ObjectType vector_orpgPlayer;
static int orpgPlayer_call_index = 0;
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
#define view_enabled GetVar(varId_view_enabled, *self)
#define _camX GetVar(varId__camX, *self)
#define _camY GetVar(varId__camY, *self)
#define os_version GetVar(varId_os_version, *self)
#define hsp GetVar(varId_hsp, *self)
#define vsp GetVar(varId_vsp, *self)
#define spd GetVar(varId_spd, *self)
#define mask_index GetVar(varId_mask_index, *self)
#define key_left GetVar(varId_key_left, *self)
#define key_right GetVar(varId_key_right, *self)
#define key_up GetVar(varId_key_up, *self)
#define key_down GetVar(varId_key_down, *self)
#define key_run GetVar(varId_key_run, *self)
#define key_run_2 GetVar(varId_key_run_2, *self)
#define key_run_3 GetVar(varId_key_run_3, *self)
#define key_jump GetVar(varId_key_jump, *self)
#define key_jump_2 GetVar(varId_key_jump_2, *self)
#define key_jump_3 GetVar(varId_key_jump_3, *self)
#define key_crouch GetVar(varId_key_crouch, *self)
#define key_crouch_2 GetVar(varId_key_crouch_2, *self)
#define key_crouch_3 GetVar(varId_key_crouch_3, *self)
#define key_Start GetVar(varId_key_Start, *self)
#define debugCR GetVar(varId_debugCR, *self)
#define jumpKeyBuffered GetVar(varId_jumpKeyBuffered, *self)
#define jumpKeyBufferTimer GetVar(varId_jumpKeyBufferTimer, *self)
#define bufferTime GetVar(varId_bufferTime, *self)
void orpgPlayer_config() {
sprite_index = sBonWalkD;
visible = 1;
solid = 0;
persistent = 0;
}

void orpgPlayer_create() {

/// @description Inserte aquí la descripción
// Puede escribir su código en este editor
controlsSetup();

/*	bufferTime = 150;

	jumpKeyBuffered = 0;
	jumpKeyBufferTimer = 0;
*/
audio_play_sound(mu_overworldRPG, 0, 1);
hsp = 0;
vsp = 0;
spd = 2;

mask_index = sHitbox;
}

void orpgPlayer_step() {

/// @description Inserte aquí la descripción
// Puede escribir su código en este editor
scr_getinput();

/*	gamepad_set_axis_deadzone(0, 0.27);

	key_left =
		keyboard_check(ord("A"))
		|| (gamepad_axis_value(0, gp_axislh) < 0)
		|| gamepad_button_check(0, gp_padl);
	key_left = clamp(key_left, 0, 1);

	key_right =
		keyboard_check(ord("D"))
		|| (gamepad_axis_value(0, gp_axislh) > 0)
		|| gamepad_button_check(0, gp_padr);
	key_right = clamp(key_right, 0, 1);

	key_up =
		keyboard_check(ord("W"))
		|| (gamepad_axis_value(0, gp_axislv) < 0)
		|| gamepad_button_check(0, gp_padu);
	key_up = clamp(key_up, 0, 1);

	key_down =
		keyboard_check(ord("S"))
		|| (gamepad_axis_value(0, gp_axislv) > 0)
		|| gamepad_button_check(0, gp_padd);
	key_down = clamp(key_down, 0, 1);

	//ACTIONS
	key_run = keyboard_check(ord("O")) || gamepad_button_check(0, gp_face3);
	key_run_2 =
		keyboard_check_pressed(ord("O")) || gamepad_button_check_pressed(0, gp_face3);
	key_run_3 =
		keyboard_check_released(ord("O")) || gamepad_button_check_released(0, gp_face3);

	key_jump = keyboard_check(ord("P")) || gamepad_button_check(0, gp_face1);
	key_jump = clamp(key_jump, 0, 1);

	key_jump_2 =
		keyboard_check_pressed(ord("P")) || gamepad_button_check_pressed(0, gp_face1);
	key_jump_2 = clamp(key_jump_2, 0, 1);

	if (key_jump_2) {
		jumpKeyBufferTimer = bufferTime;
	}
	if (jumpKeyBufferTimer > 0) {
		jumpKeyBuffered = 1;
		jumpKeyBufferTimer--;
	} else {
		jumpKeyBuffered = 0;
	}

	key_jump_3 =
		keyboard_check_released(ord("P")) || gamepad_button_check_released(0, gp_face1);
	key_jump_3 = clamp(key_jump_3, 0, 1);

	//Jump key Buffering

	key_crouch =
		keyboard_check(vk_shift)
		|| gamepad_button_check(0, gp_face2)
		|| gamepad_button_check(0, gp_shoulderrb);
	key_crouch = clamp(key_crouch, 0, 1);

	key_crouch_2 =
		keyboard_check_pressed(vk_shift)
		|| gamepad_button_check_pressed(0, gp_face2)
		|| gamepad_button_check_pressed(0, gp_shoulderrb);
	key_crouch_2 = clamp(key_crouch_2, 0, 1);

	key_crouch_3 =
		keyboard_check_released(vk_shift)
		|| gamepad_button_check_released(0, gp_face2)
		|| gamepad_button_check_released(0, gp_shoulderrb);
	key_crouch_3 = clamp(key_crouch_3, 0, 1);

	key_Start =
		keyboard_check_pressed(vk_space) || gamepad_button_check_pressed(0, gp_start);

	debugCR =
		keyboard_check_pressed(ord("C")) || gamepad_button_check_pressed(0, gp_select);
*/
hsp = (key_right - key_left) * spd;

vsp = (key_down - key_up) * spd;

image_speed = 0;

//move up
if (key_up) {
	image_speed = 1;
	sprite_index = sBonWalkU;
}

//move down
if (key_down) {
	image_speed = 1;
	sprite_index = sBonWalkD;
}

//move right
if (key_right) {
	image_speed = 1;
	sprite_index = sBonWalkR;
}

//move left
if (key_left) {
	image_speed = 1;
	sprite_index = sBonWalkL;
}

if (!key_left && !key_right && !key_down && !key_up) {
	image_index = 1;
}

if (place_meeting(x + hsp, y, orpgWall)) {
	hsp = 0;
}

if (place_meeting(x, y + vsp, orpgWall)) {
	vsp = 0;
}

x += hsp;
y += vsp;

//camera
//camera_set_view_pos(view_camera[0], x-camera_get_view_width(view_camera[0])/2,y-camera_get_view_height(view_camera[0])/2); 


//draw_boundbox();
}
void orpgPlayer_draw() {
draw_self();
}

#undef x
#undef y
#undef image_xscale
#undef image_yscale
#undef id
void orpgPlayer_precreate(float NEWX, float NEWY, float NEWXSCALE, float NEWYSCALE, float NEWID) {
Object inst;
inst.GetVar(varId_x) = NEWX;
inst.GetVar(varId_y) = NEWY;
inst.GetVar(varId_image_xscale) = NEWXSCALE;
inst.GetVar(varId_image_yscale) = NEWYSCALE;
inst.GetVar(varId_id) = NEWID;
vector_orpgPlayer.instances.push_back(inst);
self = &vector_orpgPlayer.instances.back();
orpgPlayer_config();
orpgPlayer_create();
}

void orpgPlayer_reset_frame() {
	orpgPlayer_call_index = 0;
}

void orpgPlayer_runevents(float NEWX, float NEWY, float NEWXSCALE, float NEWYSCALE, float NEWID) {
	//printf("RUNNING OBJECT: orpgPlayer\n");
	bool found = false;
	for(size_t j = 0; j < vector_orpgPlayer.instances.size(); j++){
		if(vector_orpgPlayer.instances[j].GetVar(varId_id) == NEWID){
			found = true;
			break;
		}
	}
	if(!found)
		orpgPlayer_precreate(NEWX, NEWY, NEWXSCALE, NEWYSCALE, NEWID);
	for(size_t j = 0; j < vector_orpgPlayer.instances.size(); j++){
		self = &vector_orpgPlayer.instances[j];
		CurrentObjectRunning = self;
		orpgPlayer_step();
		orpgPlayer_draw();

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

