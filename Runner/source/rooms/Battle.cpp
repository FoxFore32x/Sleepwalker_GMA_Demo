// Room: Battle

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

static GMLayerBackground Battle_bg_1 = {
NULL,
4278190080
};

static LayerInstances Battle_inst_0_data[] = {
};

static GMLayerInstance Battle_inst_0 = {
Battle_inst_0_data,
0
};

static const GMLayer Battle_layers[] = {
    { LAYER_INSTANCE, 0, &Battle_inst_0 },
    { LAYER_BACKGROUND, 100, &Battle_bg_1 },
};

static GMViewPorts Battle_views[] = {
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

GMRoom Battle_INFO = {
5,
"Battle",
1366,
768,
0,
0,
0,
1,
0,
0,
Battle_views,
8,
0,
0,
0,
10,
0.10,
Battle_layers,
sizeof(Battle_layers) / sizeof(GMLayer)
};


void scr_runroom_Battle(){
   //printf("RUNNING ROOM Battle\n");

   if (Battle_views[0].visible == 1){
       view0_camWidth = Battle_views[0].camWidth;
       view0_camHeight = Battle_views[0].camHeight;
   }
   else{
       view0_camWidth = Battle_INFO.width;
       view0_camHeight = Battle_INFO.height;
   }

   for(int i = 0; i < Battle_INFO.viewCount; i++){
       if (Battle_views[i].visible == 1){
           view_camera[i] = Battle_views[i];
       }
   }

   room_width = Battle_INFO.width;
   room_height = Battle_INFO.height;
	bgcolor = Battle_bg_1.color;
}
