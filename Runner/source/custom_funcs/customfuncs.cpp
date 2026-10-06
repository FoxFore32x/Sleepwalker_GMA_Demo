//citro2d has this declared already lol
#undef function

#include "customfuncs.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../gm_funcs/drawing.h"
#include "../gm_funcs/input.h"
#include "../gm_funcs/input.h"
#include "../helpers/asset_toid.h"
#include "../gm_funcs/misc.h"
#include "../gm_funcs/collision.h"
#include "../gm_funcs/audio.h"
#include "../gm_funcs/filesystem.h"
#include "../custom_funcs/customfuncs.h"
#include "../variable_handler.h"
#include <variant>
#include "../helpers/other.h"
#include "../helpers/var_in_object_running.h"
#include "../helpers/asset_toid.h"

#define function GMvar

#pragma push_macro("spd")

#undef spd

// Los recursos de Script han cambiado para la v2.3.0 Consulta
// https://help.yoyogames.com/hc/en-us/articles/360005277377 para más información
function evMapScroll(GMvar dir, GMvar dist, GMvar spd) {
	xDir = 0;
	yDir = 0;
	scSpeed = 0;

	switch (spd) {
		case 1: //x8 Slowest
			scSpeed = 0.25f;
			break;
		case 2: //x4 Slower
			scSpeed = 0.5f;
			break;
		case 3: //x2 Slow
			scSpeed = 1;
			break;
		case 4: //Normal
			scSpeed = 2;
			break;
		case 5: //x2 Fast
			scSpeed = 4;
			break;
		case 6: //x4 Faster
			scSpeed = 8;
			break;
	}
	switch (dir) {
		case 0: //UP
			for (i = 0; i < 32 * dist; i++) {
				yDir -= scSpeed;
				camera_set_view_pos(view_camera[0], xDir, yDir);
			}
			break;
		case 1: //DOWN
			for (i = 0; i < 32 * dist; i++) {
				yDir += scSpeed;
				camera_set_view_pos(view_camera[0], xDir, yDir);
			}
			break;
		case 2: //LEFT
			for (i = 0; i < 32 * dist; i++) {
				xDir -= scSpeed;
				camera_set_view_pos(view_camera[0], xDir, yDir);
			}
			break;
		case 3: //RIGHT
			for (i = 0; i < 32 * dist; i++) {
				xDir += scSpeed;
				camera_set_view_pos(view_camera[0], xDir, yDir);
			}
			break;
	}

	return GMvar();
}

#pragma pop_macro("spd")


// Los recursos de Script han cambiado para la v2.3.0 Consulta
// https://help.yoyogames.com/hc/en-us/articles/360005277377 para más información
function controlsSetup() {
	bufferTime = 150;

	jumpKeyBuffered = 0;
	jumpKeyBufferTimer = 0;

	return GMvar();
}

function scr_getinput() {
	gamepad_set_axis_deadzone(0, 0.27);

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

	return GMvar();
}


