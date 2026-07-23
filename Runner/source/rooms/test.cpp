// Room: test

#include "../gml/structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../helpers/asset_toid.h"
#include "../gm_funcs/drawing.h"
#include "../gm_funcs/misc.h"
#include "../gm_funcs/audio.h"
#include "../gm_funcs/filesystem.h"
#include "../helpers/asset_toid.h"

bool test_viewInit = false;

static GMLayerBackground test_bg_9 = {
NULL,
4278190080
};

static LayerInstances test_inst_0_data[] = {
    { 32, 240, 0, 6, 4, orpgWall, 100000 },
    { 320, 240, 0, 6, 4, orpgWall, 100001 },
    { 32, 32, 0, 6.75, 3.50, orpgWall, 100002 },
    { 296, 32, 0, 6.75, 3.50, orpgWall, 100003 },
    { 240, 32, 0, 2, 2, orpgWall, 100004 },
    { 368, 336, 0, 2, 2.12, orpgWall, 100005 },
    { 504, 0, 0, 1.25, 18, orpgWall, 100006 },
    { 0, 536, 0, 16, 1.25, orpgWall, 100007 },
    { 0, 0, 0, 1.25, 17, orpgWall, 100008 },
    { 32, 0, 0, 15, 1, orpgWall, 100009 },
};

static GMLayerInstance test_inst_0 = {
test_inst_0_data,
10
};

static LayerInstances test_inst_3_data[] = {
    { 0, 0, 0, 1, 1, oNXCon, 100010 },
    { 272, 128, 0, 1, 1, orpgPlayer, 100011 },
    { 32, 0, 0, 1, 1, oCamera, 100012 },
};

static GMLayerInstance test_inst_3 = {
test_inst_3_data,
3
};

static const GMLayer test_layers[] = {
    { LAYER_INSTANCE, 0, &test_inst_0 },
    { 0, 100, NULL },
    { 0, 200, NULL },
    { LAYER_INSTANCE, 300, &test_inst_3 },
    { 0, 400, NULL },
    { 0, 500, NULL },
    { 0, 600, NULL },
    { 0, 700, NULL },
    { 0, 800, NULL },
    { LAYER_BACKGROUND, 900, &test_bg_9 },
};

static GMViewPorts test_views[] = {
    {
0,
0,
544,
416,
0,
0,
544,
416,
32,
32,
-1,
-1,
0,
0,
orpgPlayer
    },
    {
0,
0,
1366,
768,
0,
0,
1366,
768,
32,
32,
-1,
-1,
0,
0,
0
    },
    {
0,
0,
1366,
768,
0,
0,
1366,
768,
32,
32,
-1,
-1,
0,
0,
0
    },
    {
0,
0,
1366,
768,
0,
0,
1366,
768,
32,
32,
-1,
-1,
0,
0,
0
    },
    {
0,
0,
1366,
768,
0,
0,
1366,
768,
32,
32,
-1,
-1,
0,
0,
0
    },
    {
0,
0,
1366,
768,
0,
0,
1366,
768,
32,
32,
-1,
-1,
0,
0,
0
    },
    {
0,
0,
1366,
768,
0,
0,
1366,
768,
32,
32,
-1,
-1,
0,
0,
0
    },
    {
0,
0,
1366,
768,
0,
0,
1366,
768,
32,
32,
-1,
-1,
0,
0,
0
    }
};

GMRoom test_INFO = {
6,
"test",
544,
576,
0,
0,
0,
1,
0,
0,
test_views,
8,
0,
0,
0,
10,
0.10,
test_layers,
sizeof(test_layers) / sizeof(GMLayer)
};

extern void orpgWall_runevents(float, float, float, float, float);
extern void orpgWall_reset_frame();
extern void oNXCon_runevents(float, float, float, float, float);
extern void oNXCon_reset_frame();
extern void orpgPlayer_runevents(float, float, float, float, float);
extern void orpgPlayer_reset_frame();
extern void oCamera_runevents(float, float, float, float, float);
extern void oCamera_reset_frame();

void scr_runroom_test(){
   //printf("RUNNING ROOM test\n");

   if(test_INFO.enableViews == 1){
       view_enabled = true;
   }
   else{
       view_enabled = false;
   }

   //if (test_views[0].visible == 1){
       view0_camWidth = test_views[0].camWidth;
       view0_camHeight = test_views[0].camHeight;
   /*}
   else{
       view0_camWidth = test_INFO.width;
       view0_camHeight = test_INFO.height;
   }*/

   if(view_enabled){
        if(!test_viewInit){
            for(int i = 0; i < test_INFO.viewCount; i++){
                view_camera[i] = test_views[i];
            }
            test_viewInit = true;
        }
        for(int i = 0; i < test_INFO.viewCount; i++) view_camera[i].visible = view_visible[i];
    } else {
        if(!test_viewInit){
            view_camera[0].camXPos = 0;
            view_camera[0].camYPos = 0;
            view_camera[0].camWidth = test_INFO.width;
            view_camera[0].camHeight = test_INFO.height;
            test_viewInit = true;
        }
    }

   room_width = test_INFO.width;
   room_height = test_INFO.height;
	bgcolor = test_bg_9.color;
	oCamera_reset_frame();
	orpgPlayer_reset_frame();
	oNXCon_reset_frame();
	orpgWall_reset_frame();
	orpgWall_runevents(test_inst_0_data[0].x, test_inst_0_data[0].y, test_inst_0_data[0].scaleX, test_inst_0_data[0].scaleY, test_inst_0_data[0].id);
	orpgWall_runevents(test_inst_0_data[1].x, test_inst_0_data[1].y, test_inst_0_data[1].scaleX, test_inst_0_data[1].scaleY, test_inst_0_data[1].id);
	orpgWall_runevents(test_inst_0_data[2].x, test_inst_0_data[2].y, test_inst_0_data[2].scaleX, test_inst_0_data[2].scaleY, test_inst_0_data[2].id);
	orpgWall_runevents(test_inst_0_data[3].x, test_inst_0_data[3].y, test_inst_0_data[3].scaleX, test_inst_0_data[3].scaleY, test_inst_0_data[3].id);
	orpgWall_runevents(test_inst_0_data[4].x, test_inst_0_data[4].y, test_inst_0_data[4].scaleX, test_inst_0_data[4].scaleY, test_inst_0_data[4].id);
	orpgWall_runevents(test_inst_0_data[5].x, test_inst_0_data[5].y, test_inst_0_data[5].scaleX, test_inst_0_data[5].scaleY, test_inst_0_data[5].id);
	orpgWall_runevents(test_inst_0_data[6].x, test_inst_0_data[6].y, test_inst_0_data[6].scaleX, test_inst_0_data[6].scaleY, test_inst_0_data[6].id);
	orpgWall_runevents(test_inst_0_data[7].x, test_inst_0_data[7].y, test_inst_0_data[7].scaleX, test_inst_0_data[7].scaleY, test_inst_0_data[7].id);
	orpgWall_runevents(test_inst_0_data[8].x, test_inst_0_data[8].y, test_inst_0_data[8].scaleX, test_inst_0_data[8].scaleY, test_inst_0_data[8].id);
	orpgWall_runevents(test_inst_0_data[9].x, test_inst_0_data[9].y, test_inst_0_data[9].scaleX, test_inst_0_data[9].scaleY, test_inst_0_data[9].id);
	oNXCon_runevents(test_inst_3_data[0].x, test_inst_3_data[0].y, test_inst_3_data[0].scaleX, test_inst_3_data[0].scaleY, test_inst_3_data[0].id);
	orpgPlayer_runevents(test_inst_3_data[1].x, test_inst_3_data[1].y, test_inst_3_data[1].scaleX, test_inst_3_data[1].scaleY, test_inst_3_data[1].id);
	oCamera_runevents(test_inst_3_data[2].x, test_inst_3_data[2].y, test_inst_3_data[2].scaleX, test_inst_3_data[2].scaleY, test_inst_3_data[2].id);
}
