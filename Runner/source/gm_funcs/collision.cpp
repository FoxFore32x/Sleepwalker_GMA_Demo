#include <stdio.h>
#include <string.h>
#include "drawing.h"
#include "misc.h"
#include "../helpers/get_spriteinfo.h"
#include "../helpers/var_in_object_running.h"


//helper funcs
void draw_boundbox(){
    int line_thick = 6;
    int boundingbox_left = x + (SpriteCollideLEFT[sprite_index] - sprite_get_xoffset(sprite_index)) * (double)image_xscale;
    int boundingbox_right = x + (SpriteCollideRIGHT[sprite_index] - sprite_get_xoffset(sprite_index)) * (double)image_xscale;
    int boundingbox_top = y + (SpriteCollideTOP[sprite_index] - sprite_get_yoffset(sprite_index)) * (double)image_yscale;
    int boundingbox_bottom = y + (SpriteCollideBOTTOM[sprite_index] - sprite_get_yoffset(sprite_index)) * (double)image_yscale;
    #ifdef __3DS__
        if (sprite_index < 0)
            return;

        //draw bounding box
        C2D_DrawLine(boundingbox_left, boundingbox_top, C2D_Color32(255, 0, 0, 255), boundingbox_right, boundingbox_top, C2D_Color32(255, 0, 0, 255), line_thick, 0.0f);
        C2D_DrawLine(boundingbox_right, boundingbox_top, C2D_Color32(255, 0, 0, 255), boundingbox_right, boundingbox_bottom, C2D_Color32(255, 0, 0, 255), line_thick, 0.0f);
        C2D_DrawLine(boundingbox_right, boundingbox_bottom, C2D_Color32(255, 0, 0, 255), boundingbox_left, boundingbox_bottom, C2D_Color32(255, 0, 0, 255), line_thick, 0.0f);
        C2D_DrawLine(boundingbox_left, boundingbox_bottom, C2D_Color32(255, 0, 0, 255), boundingbox_left, boundingbox_top, C2D_Color32(255, 0, 0, 255), line_thick, 0.0f);
    #endif
}

//the gm funcs
bool place_meeting(float _x, float _y, ObjectType& object_vector){
    if (sprite_index < 0)
        return false;


    float boundingbox_left = 0;
    float boundingbox_right = 0;
    float boundingbox_top = 0;
    float boundingbox_bottom = 0;

    if(self->HasVar(varId_mask_index)){
        //set bounding box
        boundingbox_left = _x + (SpriteCollideLEFT[mask_index] - sprite_get_xoffset(mask_index)) * image_xscale;
        boundingbox_right = _x + (SpriteCollideRIGHT[mask_index] - sprite_get_xoffset(mask_index)) * image_xscale;
        boundingbox_top = _y + (SpriteCollideTOP[mask_index] - sprite_get_yoffset(mask_index)) * image_yscale;
        boundingbox_bottom = _y + (SpriteCollideBOTTOM[mask_index] - sprite_get_yoffset(mask_index)) * image_yscale;
    }else {
        //set bounding box
        boundingbox_left = _x + (SpriteCollideLEFT[sprite_index] - sprite_get_xoffset(sprite_index)) * image_xscale;
        boundingbox_right = _x + (SpriteCollideRIGHT[sprite_index] - sprite_get_xoffset(sprite_index)) * image_xscale;
        boundingbox_top = _y + (SpriteCollideTOP[sprite_index] - sprite_get_yoffset(sprite_index)) * image_yscale;
        boundingbox_bottom = _y + (SpriteCollideBOTTOM[sprite_index] - sprite_get_yoffset(sprite_index)) * image_yscale;
    }

    float x1 = min(boundingbox_left, boundingbox_right);
    float x2 = max(boundingbox_left, boundingbox_right);
    float y1 = min(boundingbox_top, boundingbox_bottom);
    float y2 = max(boundingbox_top, boundingbox_bottom);

    #undef sprite_index
    #undef image_xscale
    #undef image_yscale
    #undef mask_index

    for (Object& other : object_vector.instances)
    {
        // optionally skip self
        if (&other == CurrentObjectRunning)
            continue;

        float boundingbox_left_other = 0;
        float boundingbox_right_other = 0;
        float boundingbox_top_other = 0;
        float boundingbox_bottom_other = 0;

        if (other.HasVar(varId_mask_index)){
            boundingbox_left_other = other.GetVar(varId_x) + (SpriteCollideLEFT[other.GetVar(varId_mask_index)] - sprite_get_xoffset(other.GetVar(varId_mask_index))) * other.GetVar(varId_image_xscale);
            boundingbox_right_other = other.GetVar(varId_x) + (SpriteCollideRIGHT[other.GetVar(varId_mask_index)] - sprite_get_xoffset(other.GetVar(varId_mask_index))) * other.GetVar(varId_image_xscale);
            boundingbox_top_other = other.GetVar(varId_y) + (SpriteCollideTOP[other.GetVar(varId_mask_index)] - sprite_get_yoffset(other.GetVar(varId_mask_index))) * other.GetVar(varId_image_yscale);
            boundingbox_bottom_other = other.GetVar(varId_y) + (SpriteCollideBOTTOM[other.GetVar(varId_mask_index)] - sprite_get_yoffset(other.GetVar(varId_mask_index))) * other.GetVar(varId_image_yscale);
        } else {
            boundingbox_left_other = other.GetVar(varId_x) + (SpriteCollideLEFT[other.GetVar(varId_sprite_index)] - sprite_get_xoffset(other.GetVar(varId_sprite_index))) * other.GetVar(varId_image_xscale);
            boundingbox_right_other = other.GetVar(varId_x) + (SpriteCollideRIGHT[other.GetVar(varId_sprite_index)] - sprite_get_xoffset(other.GetVar(varId_sprite_index))) * other.GetVar(varId_image_xscale);
            boundingbox_top_other = other.GetVar(varId_y) + (SpriteCollideTOP[other.GetVar(varId_sprite_index)] - sprite_get_yoffset(other.GetVar(varId_sprite_index))) * other.GetVar(varId_image_yscale);
            boundingbox_bottom_other = other.GetVar(varId_y) + (SpriteCollideBOTTOM[other.GetVar(varId_sprite_index)] - sprite_get_yoffset(other.GetVar(varId_sprite_index))) * other.GetVar(varId_image_yscale);
        }
        float x1_other = min(boundingbox_left_other, boundingbox_right_other);
        float x2_other = max(boundingbox_left_other, boundingbox_right_other);
        float y1_other = min(boundingbox_top_other, boundingbox_bottom_other);
        float y2_other = max(boundingbox_top_other, boundingbox_bottom_other);

        bool isColliding = (x2 > x1_other && x1 < x2_other && y2 > y1_other && y1 < y2_other);
        if (isColliding)
            return true;
    }
    
    return false;
}

bool place_empty(float _x, float _y, int object){
    return true;
}

bool place_free(float _x, float _y){
    return true;
}

bool position_empty(float _x, float _y){
    return true;
}

bool position_meeting(float _x, float _y, int object){
    return false;
}

void position_destroy(float _x, float _y){
    //so empty...
}

int instance_place(float _x, float _y, int object){
    return 0;
}

int instance_position(float _x, float _y, int object){
    return 0;
}
