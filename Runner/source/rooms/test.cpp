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

static const int test_tile_1_data[] = {
    -120,-2147483648,1,22,-5,60,-3,-2147483648,-5,60,1,23,-171,-2147483648,
};

static GMLayerTile test_tile_1[] = {
    tlDowan1, test_tile_1_data, 0, 0, 0
};

static const int test_tile_2_data[] = {
    -18,-2147483648,1,40,-13,41,4,42,-2147483648,-2147483648,48,-6,-2147483648,1,0,-6,-2147483648,4,50,-2147483648,
          -2147483648,48,-5,-2147483648,-3,0,-5,-2147483648,4,50,-2147483648,-2147483648,48,-5,-2147483648,-3,
          0,-5,-2147483648,4,50,-2147483648,-2147483648,48,-6,-2147483648,1,0,-6,-2147483648,4,50,-2147483648,
          -2147483648,48,-13,-2147483648,4,50,-2147483648,-2147483648,48,-13,-2147483648,4,50,-2147483648,-2147483648,
          48,-13,-2147483648,4,50,-2147483648,-2147483648,48,-12,-2147483648,5,0,50,-2147483648,-2147483648,48,
          -12,-2147483648,5,0,50,-2147483648,-2147483648,48,-12,-2147483648,5,0,50,-2147483648,-2147483648,48,
          -12,-2147483648,5,0,50,-2147483648,-2147483648,48,-12,-2147483648,5,0,50,-2147483648,-2147483648,48,
          -12,-2147483648,5,0,50,-2147483648,-2147483648,48,-13,-2147483648,4,50,-2147483648,-2147483648,56,-13,
          57,1,58,-5,-2147483648,-2,0,-11,-2147483648,
};

static GMLayerTile test_tile_2[] = {
    tlDowan1, test_tile_2_data, 0, 0, 0
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

static const int test_tile_4_data[] = {
    -181,-2147483648,3,8,9,10,-14,-2147483648,3,16,17,18,-14,-2147483648,3,24,25,26,-88,-2147483648,
};

static GMLayerTile test_tile_4[] = {
    tlDowan2, test_tile_4_data, 0, 0, 0
};

static const int test_tile_5_data[] = {
    -4,0,-8,-2147483648,-24,0,-6,-2147483648,1,0,-6,-2147483648,-4,0,-5,-2147483648,3,50,41,48,-5,-2147483648,
          -4,0,-5,-2147483648,3,50,-2147483648,48,-5,-2147483648,-6,0,-11,-2147483648,-6,0,-11,-2147483648,-5,
          0,-12,-2147483648,-4,0,-13,-2147483648,-4,0,-12,-2147483648,-5,0,-12,-2147483648,-5,0,-12,-2147483648,
          -5,0,-12,-2147483648,-5,0,-12,-2147483648,-5,0,-12,-2147483648,-5,0,-13,-2147483648,-36,0,
};

static GMLayerTile test_tile_5[] = {
    tlDowan1, test_tile_5_data, 0, 0, 0
};

static const int test_tile_6_data[] = {
    -288,-2147483648,-2,2,-18,-2147483648,1,2,-12,-2147483648,-4,2,-12,-2147483648,1,2,-446,-2147483648,
          1,2,-28,-2147483648,1,2,-410,-2147483648,
};

static GMLayerTile test_tile_6[] = {
    tlShadow, test_tile_6_data, 0, 0, 0
};

static const int test_tile_7_data[] = {
    -38,-2147483648,1,12,-8,-2147483648,1,12,-21,-2147483648,-7,11,1,52,-7,11,-4,-2147483648,12,13,14,15,
          -2147483648,30,28,31,-2147483648,-2147483648,13,14,15,-9,-2147483648,3,46,49,47,-8,-2147483648,-15,0,
          -2,-2147483648,-6,41,3,19,36,21,-6,41,-4,-2147483648,1,12,-3,-2147483648,3,27,36,29,-14,-2147483648,
          3,27,36,29,-8,-2147483648,-6,11,3,27,36,29,-6,11,-2,-2147483648,9,0,13,14,15,-2147483648,-2147483648,
          35,36,37,-8,-2147483648,1,0,-15,-2147483648,-5,0,-12,-2147483648,-5,0,-13,-2147483648,-4,0,-13,-2147483648,
          -2,0,-14,-2147483648,
};

static GMLayerTile test_tile_7[] = {
    tlDowan1, test_tile_7_data, 0, 0, 0
};

static const int test_tile_8_data[] = {
    -86,-2147483648,-2,4,-3,-2147483648,1,3,-3,-2147483648,2,3,4,-3,-2147483648,9,4,-2147483648,-2147483648,
          4,4,3,4,4,3,-3,-2147483648,3,3,4,3,-3,4,-2,-2147483648,-2,4,10,3,4,4,3,4,3,4,3,4,3,-3,4,-70,-2147483648,
          1,3,-3,-2147483648,-2,3,15,0,-2147483648,-2147483648,3,4,3,4,3,4,-2147483648,-2147483648,3,3,4,4,-3,
          3,14,4,3,3,4,3,4,3,4,-2147483648,-2147483648,3,3,4,4,-3,3,14,4,3,3,4,3,4,3,4,-2147483648,-2147483648,
          3,3,4,4,-3,3,14,4,3,3,4,3,4,3,4,-2147483648,-2147483648,3,3,4,4,-3,3,8,4,3,3,4,3,4,3,4,-18,-2147483648,
};

static GMLayerTile test_tile_8[] = {
    tlDowan1, test_tile_8_data, 0, 0, 0
};

static const GMLayer test_layers[] = {
    { "wall", LAYER_INSTANCE, 0, &test_inst_0, false},
    { "Fence", LAYER_TILE, 100, &test_tile_1, true},
    { "Frame", LAYER_TILE, 200, &test_tile_2, true},
    { "Instances", LAYER_INSTANCE, 300, &test_inst_3, true},
    { "Objects", LAYER_TILE, 400, &test_tile_4, true},
    { "Door", LAYER_TILE, 500, &test_tile_5, true},
    { "Shadow", LAYER_TILE, 600, &test_tile_6, true},
    { "Decoration", LAYER_TILE, 700, &test_tile_7, true},
    { "Floor", LAYER_TILE, 800, &test_tile_8, true},
    { "Background", LAYER_BACKGROUND, 900, &test_bg_9, true},
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

extern void orpgWall_runevents(float, float, float, float, float, bool);
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
    placeHolderTileRoomFunc(test_tile_8->tileset, test_tile_8->data, sizeof(test_tile_8_data) / sizeof(test_tile_8_data[0]), room_width);
    placeHolderTileRoomFunc(test_tile_7->tileset, test_tile_7->data, sizeof(test_tile_7_data) / sizeof(test_tile_7_data[0]), room_width);
    placeHolderTileRoomFunc(test_tile_6->tileset, test_tile_6->data, sizeof(test_tile_6_data) / sizeof(test_tile_6_data[0]), room_width);
    placeHolderTileRoomFunc(test_tile_5->tileset, test_tile_5->data, sizeof(test_tile_5_data) / sizeof(test_tile_5_data[0]), room_width);
    placeHolderTileRoomFunc(test_tile_4->tileset, test_tile_4->data, sizeof(test_tile_4_data) / sizeof(test_tile_4_data[0]), room_width);
    oCamera_runevents(test_inst_3_data[2].x, test_inst_3_data[2].y, test_inst_3_data[2].scaleX, test_inst_3_data[2].scaleY, test_inst_3_data[2].id);
    orpgPlayer_runevents(test_inst_3_data[1].x, test_inst_3_data[1].y, test_inst_3_data[1].scaleX, test_inst_3_data[1].scaleY, test_inst_3_data[1].id);
    oNXCon_runevents(test_inst_3_data[0].x, test_inst_3_data[0].y, test_inst_3_data[0].scaleX, test_inst_3_data[0].scaleY, test_inst_3_data[0].id);
    placeHolderTileRoomFunc(test_tile_2->tileset, test_tile_2->data, sizeof(test_tile_2_data) / sizeof(test_tile_2_data[0]), room_width);
    placeHolderTileRoomFunc(test_tile_1->tileset, test_tile_1->data, sizeof(test_tile_1_data) / sizeof(test_tile_1_data[0]), room_width);
	orpgWall_runevents(test_inst_0_data[0].x, test_inst_0_data[0].y, test_inst_0_data[0].scaleX, test_inst_0_data[0].scaleY, test_inst_0_data[0].id, test_layers[0].visible);
	orpgWall_runevents(test_inst_0_data[1].x, test_inst_0_data[1].y, test_inst_0_data[1].scaleX, test_inst_0_data[1].scaleY, test_inst_0_data[1].id, test_layers[0].visible);
	orpgWall_runevents(test_inst_0_data[2].x, test_inst_0_data[2].y, test_inst_0_data[2].scaleX, test_inst_0_data[2].scaleY, test_inst_0_data[2].id, test_layers[0].visible);
	orpgWall_runevents(test_inst_0_data[3].x, test_inst_0_data[3].y, test_inst_0_data[3].scaleX, test_inst_0_data[3].scaleY, test_inst_0_data[3].id, test_layers[0].visible);
	orpgWall_runevents(test_inst_0_data[4].x, test_inst_0_data[4].y, test_inst_0_data[4].scaleX, test_inst_0_data[4].scaleY, test_inst_0_data[4].id, test_layers[0].visible);
	orpgWall_runevents(test_inst_0_data[5].x, test_inst_0_data[5].y, test_inst_0_data[5].scaleX, test_inst_0_data[5].scaleY, test_inst_0_data[5].id, test_layers[0].visible);
	orpgWall_runevents(test_inst_0_data[6].x, test_inst_0_data[6].y, test_inst_0_data[6].scaleX, test_inst_0_data[6].scaleY, test_inst_0_data[6].id, test_layers[0].visible);
	orpgWall_runevents(test_inst_0_data[7].x, test_inst_0_data[7].y, test_inst_0_data[7].scaleX, test_inst_0_data[7].scaleY, test_inst_0_data[7].id, test_layers[0].visible);
	orpgWall_runevents(test_inst_0_data[8].x, test_inst_0_data[8].y, test_inst_0_data[8].scaleX, test_inst_0_data[8].scaleY, test_inst_0_data[8].id, test_layers[0].visible);
	orpgWall_runevents(test_inst_0_data[9].x, test_inst_0_data[9].y, test_inst_0_data[9].scaleX, test_inst_0_data[9].scaleY, test_inst_0_data[9].id, test_layers[0].visible);
}
