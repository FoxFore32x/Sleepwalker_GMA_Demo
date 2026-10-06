//these don't deserve their own file lol

//camera funcs
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "misc.h"
#include "../variable_handler.h"
#include <variant>
#include <vector>

float view0_camXPos = 0;
float view0_camYPos = 0;
float view0_camWidth = 1366;
float view0_camHeight = 768;
int os_type = CURRENT_OS;

Object* CurrentObjectRunning = NULL;

#pragma region //camera funcs
void camera_set_view_pos(GMViewPorts &view, float _x, float _y){
    view.camXPos = _x;
    view.camYPos = _y;
}

void camera_set_view_size(GMViewPorts &view, float _width, float _height){
    view.camWidth = _width;
    view.camHeight = _height;
}

void view_set_xport(int viewID, float _x){
    view_camera[viewID].viewXPos = _x;
}

void view_set_yport(int viewID, float _y){
    view_camera[viewID].viewYPos = _y;
}

void view_set_wport(int viewID, float _width){
    view_camera[viewID].viewWidth = _width;
}

void view_set_hport(int viewID, float _height){
    view_camera[viewID].viewHeight = _height;
}

float camera_get_view_width(GMViewPorts &view){
    return view.camWidth;
}

float camera_get_view_height(GMViewPorts &view){
    return view.camHeight;
}

float camera_get_view_x(GMViewPorts &view){
    return view.camXPos;
}

float camera_get_view_y(GMViewPorts &view){
    return view.camYPos;
}

#pragma endregion

#pragma region //window stuff
void window_set_caption(char* caption){
    //No
}
int window_device(){
    //No
    return 0;
}
int window_handle(char* caption){
    //No
    return 0;
}
bool window_has_focus(){
    //No
    return true;
}
void window_post_message(){
    //No
}
void window_center(){
    //No
}
bool window_get_fullscreen(){
    //No
    return true;
}
void window_set_fullscreen(bool fullscreen){
    //No
}

void window_set_size(int width, int height){
    //No
}
#pragma endregion

#pragma region //rooms
void room_goto(int room_id){
    room = room_id;
}
void room_goto_next(){
    room += 1;
}
void room_goto_previous(){
    room -= 1;
}

int room_next(int room_id){
    return room_id + 1;
}

int room_previous(int room_id){
    return room_id - 1;
}

void room_set_height(int room_id, float height){
    room_height = height;
}
void room_set_width(int room_id, float width){
    room_width = width;
}

void room_restart(){
    room_goto(room);
}

#pragma endregion

#pragma region //game_ funcs
void game_end(){
    MarkedForClose = true;
}
void game_restart(){
    //so empty...
}
#pragma endregion

#pragma region //these don't even deserve their own region lmao
bool code_is_compiled(){
    return true;
}

float display_get_width(){
    return 400;
}
float display_get_height(){
    return 240;
}

int display_get_orientation(){
    return display_landscape;
}

float display_get_frequency(){
    return 60; //I'll change this if we ever find a console that uses a different thing (actually pal is 50 hmmm, later...)
}

const char* string(GMvar value){
    static char str[64];

if (std::holds_alternative<int>(value.value))
    snprintf(str, sizeof(str), "%d", std::get<int>(value.value));
else if (std::holds_alternative<float>(value.value))
    snprintf(str, sizeof(str), "%f", std::get<float>(value.value));


    return str;
}

void show_debug_message(const char* message){
    printf("%s\n", message);
}

float clamp(float value, float min, float max){
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

float sign(float number){
    if (number > 0)
        return 1;
    else if (number < 0)
        return -1;
    else
        return 0;
}

float lerp(float value, float to_goto, float speed){
    return value + speed * (to_goto - value);
}

float lengthdir_y(float len, float dir){
    return len * sin(dir * (M_PI / 180));
}

float lengthdir_x(float len, float dir){
    return len * cos(dir * (M_PI / 180));
}

//STUB
int alarm_get(int alarm_id){
    return -1;
}


#pragma endregion

#pragma region //Objects and shit

Object& get_object(std::vector<Object>& object_vector){
    for(size_t i = 0; i < object_vector.size(); i++){
        return object_vector[i];
    }

    Object empty;
    return empty;
}

bool instance_exists(ObjectType inst){
    if (inst.instances.empty())
        return false;

    return true;
}

#pragma endregion

#pragma region //Tilesets

#pragma endregion

//3ds
#ifdef __3DS__
    #include <3ds.h>
    #include <citro2d.h>

    void show_message(const char* message){
        errorConf error;
        errorInit(&error, ERROR_TEXT, CFG_LANGUAGE_EN);
        errorText(&error, message);
        errorDisp(&error);
    }

    bool show_question(const char* message){
        return false;
    }

    void show_error(const char* message, bool abort){
        show_message(message);

        if (abort)
            game_end();
    }


#endif

//gamecube and wii
 #if defined(__gamecube__) || defined(__wii__)
    void show_message(const char* message){
        //I don't think gamecube has a thing for this?
    }
    
    bool show_question(const char* message){
        return false;
    }

    void show_error(const char* message, bool abort){
        if (abort)
            game_end();
    }
#endif

