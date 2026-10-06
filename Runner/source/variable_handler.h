#include <vector>
#include <algorithm>
#include <variant>
#include <cstdint>
#include <memory>
#include <string>

#pragma once

struct GMvar{
    std::variant<const char*, bool, float, int, std::shared_ptr<std::vector<GMvar>>> value;

    //type init
    GMvar() : value(0) {};
    GMvar(int i) :value(i) {};
    GMvar(float f) : value(f) {};
    GMvar(bool b) : value(b) {};
    GMvar(const char* s) : value(s) {};
    GMvar(const GMvar& other) : value(other.value) {};

    #pragma region //converting variable types
    //convert to float
    operator float () const{
        return std::visit([](auto && val) -> float {
            using T = std::decay_t<decltype(val)>;

            if constexpr (std::is_same_v<T, int>)
                return static_cast<float>(val);
            else if constexpr (std::is_same_v<T, bool>)
                return val ? 1.0f : 0.0f;
            else if constexpr (std::is_same_v<T, const char*>)
                return 0.0f;
            else if constexpr (std::is_same_v<T, std::shared_ptr<std::vector<GMvar>>>)
                return 0.0f; // arrays don't convert to a number
            else
                return val;
        }, value);
    }

    //convert to int
    operator int() const{
        return (int)(float)*this;
    }

    //convert to bool
    explicit operator bool() const{
        return std::visit([](auto&& val) -> bool {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, bool>)
                return val;
            else if constexpr (std::is_same_v<T, int>)
                return val != 0;
            else if constexpr (std::is_same_v<T, float>)
                return val != 0.0f;
            else if constexpr (std::is_same_v<T, const char*>)
                return val != nullptr;
            else // array
                return val != nullptr;
        }, value);
    }

    //convert to const char*
    operator const char*() const {
        if (auto* s = std::get_if<const char*>(&value)) 
            return *s;

        return nullptr;
    }
    #pragma endregion

    //writing to the var
    GMvar& operator= (int i) { value = i; return *this; }
    GMvar& operator= (float f) { value = f; return *this; }
    GMvar& operator= (bool b) { value = b; return *this; }
    GMvar& operator= (const char* s) { value = s; return *this; }
    GMvar& operator= (const GMvar& other) { value = other.value; return *this; }

    //adding, subtracting, multiplying and dividing
    // +
    //Holds float or int
    GMvar operator+(float o) const{
        if (std::holds_alternative<float>(value) || std::holds_alternative<int>(value)){
            return GMvar {(float)*this + o};
        }
    }

    //Holds string
    GMvar operator+(const char* o) const{
        if (std::holds_alternative<const char*>(value)){
            return GMvar {(std::string((const char*)*this) + o).c_str()};
        }
    }

    //Holds GMvar
    GMvar operator+(const GMvar& o) const{
        if (std::holds_alternative<const char*>(value) && std::holds_alternative<const char*>(o.value)){
            return GMvar{ (std::string((const char*)*this) + (const char*)o).c_str() };
        }
        if ((std::holds_alternative<float>(value) || std::holds_alternative<int>(value)) && (std::holds_alternative<float>(o.value) || std::holds_alternative<int>(o.value))){
            return GMvar {(float)*this + (float)o};
        }
    }

    // -
    GMvar operator- (float o) const { return GMvar{(float)*this - o}; } 
    GMvar operator-(const GMvar& o) const { return GMvar {(float)*this - (float)o}; }

    // *
    GMvar operator* (float o) const { return GMvar{(float)*this * o}; } 
    GMvar operator*(const GMvar& o) const { return GMvar {(float)*this * (float)o}; }

    // /
    GMvar operator/ (float o) const { return GMvar{(float)*this / o}; } 
    GMvar operator/(const GMvar& o) const { return GMvar {(float)*this / (float)o}; }

    
    GMvar operator++ (int) { GMvar tmp(*this); value = (float)*this + 1; return tmp; } // ++
    GMvar operator-- (int) { GMvar tmp(*this); value = (float)*this - 1; return tmp; } // --
    GMvar& operator+= (float o) { value = (float)*this + o; return *this; } // +=
    GMvar& operator-= (float o) { value = (float)*this - o; return *this; } // -=
    GMvar& operator*= (float o) { value = (float)*this * o; return *this; } // *=
    GMvar& operator/= (float o) { value = (float)*this / o; return *this; } // /=

    //checking the variable
    bool operator== (float o) const { return (float)*this == o; }
    bool operator!= (float o) const { return (float)*this != o; }
    bool operator< (float o) const { return (float)*this < o; }
    bool operator> (float o) const { return (float)*this > o; }
    bool operator<= (float o) const { return (float)*this <= o; }
    bool operator>= (float o) const { return (float)*this >= o; }
};

inline GMvar operator+ (float o, const GMvar& v) { return v + o; }
inline GMvar operator- (float o, const GMvar& v) { return GMvar{o - (float)v}; }
inline GMvar operator* (float o, const GMvar& v) { return v * o; }
inline GMvar operator/ (float o, const GMvar& v) { return GMvar{o / (float)v}; }

struct VarNode{
    uint16_t vId;
    GMvar value;
};

struct Object{
    std::vector<VarNode> vars;

    GMvar& GetVar(uint16_t index){

        // find var in sorted vector using binary search
        auto it = std::lower_bound(vars.begin(), vars.end(), index, [](const VarNode& node, uint16_t id){
            return node.vId < id;
        });

        // var already exists
        if (it != vars.end() && it->vId == index)
            return it->value;

        // create var while keeping vector sorted
        it = vars.insert(it, {index, GMvar()});

        return it->value;
    }

    bool HasVar(uint16_t index) const {
        auto it = std::lower_bound(vars.begin(), vars.end(), index, [](const VarNode& node, uint16_t id){
            return node.vId < id;
        });

        return it != vars.end() && it->vId == index;
    }
};

class ObjectType {
public:
    std::vector<Object> instances;

    operator std::vector<Object>&() {
        return instances;
    }

    Object* Objects() {
        if (instances.empty())
            return nullptr;
        for(std::size_t i = 0; i < instances.size(); i++){
            return &instances[i];
        }
        return nullptr;
    }

    GMvar& GetVar(int var, Object& dummy_instance) {
        return Objects()->GetVar(var);
    }

};

inline GMvar& GetVar(int var, Object& instance) {
    return instance.GetVar(var);
}

#define var GMvar
inline VarNode globVar_x = {0, 0};
#define varId_x globVar_x.vId
inline VarNode globVar_y = {1, 0};
#define varId_y globVar_y.vId
inline VarNode globVar_sprite_index = {2, -4};
#define varId_sprite_index globVar_sprite_index.vId
inline VarNode globVar_image_xscale = {3, 1};
#define varId_image_xscale globVar_image_xscale.vId
inline VarNode globVar_image_yscale = {4, 1};
#define varId_image_yscale globVar_image_yscale.vId
inline VarNode globVar_sprite_xoffset = {5, 0};
#define varId_sprite_xoffset globVar_sprite_xoffset.vId
inline VarNode globVar_sprite_yoffset = {6, 0};
#define varId_sprite_yoffset globVar_sprite_yoffset.vId
inline VarNode globVar_image_index = {7, 0};
#define varId_image_index globVar_image_index.vId
inline VarNode globVar_alarm = {8, -1};
#define varId_alarm globVar_alarm.vId
inline VarNode globVar_id = {9, -4};
#define varId_id globVar_id.vId
inline VarNode globVar_visible = {10, false};
#define varId_visible globVar_visible.vId
inline VarNode globVar_solid = {11, false};
#define varId_solid globVar_solid.vId
inline VarNode globVar_persistent = {12, false};
#define varId_persistent globVar_persistent.vId
inline VarNode globVar_depth = {13, 0};
#define varId_depth globVar_depth.vId
inline VarNode globVar_layer = {14, -4};
#define varId_layer globVar_layer.vId
inline VarNode globVar_on_ui_layer = {15, false};
#define varId_on_ui_layer globVar_on_ui_layer.vId
inline VarNode globVar_collision_space = {16, -4};
#define varId_collision_space globVar_collision_space.vId
inline VarNode globVar_direction = {17, 0};
#define varId_direction globVar_direction.vId
inline VarNode globVar_friction = {18, 0};
#define varId_friction globVar_friction.vId
inline VarNode globVar_gravity = {19, 0};
#define varId_gravity globVar_gravity.vId
inline VarNode globVar_gravity_direction = {20, 0};
#define varId_gravity_direction globVar_gravity_direction.vId
inline VarNode globVar_hspeed = {21, 0};
#define varId_hspeed globVar_hspeed.vId
inline VarNode globVar_vspeed = {22, 0};
#define varId_vspeed globVar_vspeed.vId
inline VarNode globVar_speed = {23, 0};
#define varId_speed globVar_speed.vId
inline VarNode globVar_xstart = {24, 0};
#define varId_xstart globVar_xstart.vId
inline VarNode globVar_ystart = {25, 0};
#define varId_ystart globVar_ystart.vId
inline VarNode globVar_xprevious = {26, 0};
#define varId_xprevious globVar_xprevious.vId
inline VarNode globVar_yprevious = {27, 0};
#define varId_yprevious globVar_yprevious.vId
inline VarNode globVar_object_index = {28, 0};
#define varId_object_index globVar_object_index.vId
inline VarNode globVar_sprite_width = {29, 0};
#define varId_sprite_width globVar_sprite_width.vId
inline VarNode globVar_sprite_height = {30, 0};
#define varId_sprite_height globVar_sprite_height.vId
inline VarNode globVar_image_alpha = {31, 0};
#define varId_image_alpha globVar_image_alpha.vId
inline VarNode globVar_image_angle = {32, 0};
#define varId_image_angle globVar_image_angle.vId
inline VarNode globVar_image_blend = {33, 0};
#define varId_image_blend globVar_image_blend.vId
inline VarNode globVar_image_number = {34, 0};
#define varId_image_number globVar_image_number.vId
inline VarNode globVar_image_speed = {35, 0};
#define varId_image_speed globVar_image_speed.vId
inline VarNode globVar_finalCamX = {43, -4};
#define varId_finalCamX globVar_finalCamX.vId
inline VarNode globVar_finalCamY = {44, -4};
#define varId_finalCamY globVar_finalCamY.vId
inline VarNode globVar_camTrailSpd = {45, -4};
#define varId_camTrailSpd globVar_camTrailSpd.vId
inline VarNode globVar_view_w = {46, -4};
#define varId_view_w globVar_view_w.vId
inline VarNode globVar_view_h = {47, -4};
#define varId_view_h globVar_view_h.vId
inline VarNode globVar_view_enabled = {48, -4};
#define varId_view_enabled globVar_view_enabled.vId
inline VarNode globVar__camX = {49, -4};
#define varId__camX globVar__camX.vId
inline VarNode globVar__camY = {50, -4};
#define varId__camY globVar__camY.vId
inline VarNode globVar_os_version = {52, -4};
#define varId_os_version globVar_os_version.vId
inline VarNode globVar_hsp = {61, -4};
#define varId_hsp globVar_hsp.vId
inline VarNode globVar_vsp = {62, -4};
#define varId_vsp globVar_vsp.vId
inline VarNode globVar_spd = {63, -4};
#define varId_spd globVar_spd.vId
inline VarNode globVar_mask_index = {64, -4};
#define varId_mask_index globVar_mask_index.vId
inline VarNode globVar_key_left = {65, -4};
#define varId_key_left globVar_key_left.vId
inline VarNode globVar_key_right = {66, -4};
#define varId_key_right globVar_key_right.vId
inline VarNode globVar_key_up = {67, -4};
#define varId_key_up globVar_key_up.vId
inline VarNode globVar_key_down = {68, -4};
#define varId_key_down globVar_key_down.vId
//Manually added variables
inline VarNode globVar_key_run = {69, -4};
#define varId_key_run globVar_key_run.vId
inline VarNode globVar_key_run_2 = {70, -4};
#define varId_key_run_2 globVar_key_run_2.vId
inline VarNode globVar_key_run_3 = {71, -4};
#define varId_key_run_3 globVar_key_run_3.vId
inline VarNode globVar_key_jump = {72, -4};
#define varId_key_jump globVar_key_jump.vId
inline VarNode globVar_key_jump_2 = {73, -4};
#define varId_key_jump_2 globVar_key_jump_2.vId
inline VarNode globVar_key_jump_3 = {74, -4};
#define varId_key_jump_3 globVar_key_jump_3.vId
inline VarNode globalVar_key_crouch = {75, -4};
#define varId_key_crouch globalVar_key_crouch.vId
inline VarNode globalVar_key_crouch_2 = {76, -4};
#define varId_key_crouch_2 globalVar_key_crouch_2.vId
inline VarNode globalVar_key_crouch_3 = {77, -4};
#define varId_key_crouch_3 globalVar_key_crouch_3.vId
inline VarNode globalVar_key_Start = {78, -4};
#define varId_key_Start globalVar_key_Start.vId
inline VarNode globalVar_debugCR = {79, -4};
#define varId_debugCR globalVar_debugCR.vId
inline VarNode globalVar_jumpKeyBuffered = {80, -4};
#define varId_jumpKeyBuffered globalVar_jumpKeyBuffered.vId
inline VarNode globalVar_jumpKeyBufferTimer = {81, -4};
#define varId_jumpKeyBufferTimer globalVar_jumpKeyBufferTimer.vId
inline VarNode globalVar_bufferTime = {82, -4};
#define varId_bufferTime globalVar_bufferTime.vId
inline VarNode globalVar_xDir = {83, -4};
#define varId_xDir globalVar_xDir.vId
inline VarNode globalVar_yDir = {84, -4};
#define varId_yDir globalVar_yDir.vId
inline VarNode globalVar_scSpeed = {85, -4};
#define varId_scSpeed globalVar_scSpeed.vId
inline VarNode globalVar_i = {86, -4};
#define varId_i globalVar_i.vId
struct global_bleh {
GMvar nxgp = 0;
};
inline global_bleh global;

extern Object* self; 
extern ObjectType vector_orpgPlayer;
extern ObjectType vector_orpgWall;
extern ObjectType vector_oCamera;