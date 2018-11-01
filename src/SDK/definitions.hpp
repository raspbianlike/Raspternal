#ifndef RASPTERNAL_DEFINITIONS_HPP
#define RASPTERNAL_DEFINITIONS_HPP

#include <stdint-gcc.h>
#include "Vector.hpp"

struct Entity {
    char __buf_0x00[0x94]; // 0x0
    int index;// 0x94
    char __buf_0x98[0x34]; // 0x98
    Vector absVelocity; // 0xCC
    Vector absOrigin; // 0xD8
    Vector origin; // 0xE4
    Vector angVelocity; // 0xF0
    Vector absRotation; // 0xFC
    Vector rotation; // 0x108
    float gravity; // 0x114
    float proxyRandomValue; // 0x118
    int eFlags; // 0x11C
    unsigned char waterType; // 0x120
    unsigned char dormant; // 0x121
    char __buf_0x122[0x2]; // 0x122
    float effects; // 0x124
    int teamNum; // 0x128
    int pendingTeamNum; // 0x12C
    char __buf_0x130[0x4]; // 0x130
    int health; // 0x134
    int flags; // 0x138
    Vector viewOffset; // 0x13C
    Vector velocity; // 0x148
    Vector baseVelocity; // 0x154
    Vector networkAngles; // 0x160
    Vector networkOrigin; // 0x16C
};

class EntityInfo {
public:
    Entity entity;
    uintptr_t entityPtr;
};

struct BoneMatrix {
    char __buff_0x00[0xC];//0x00
    float x;//0xC
    char __buff_0x10[0xC];//0x10
    float y;//0x1c
    char __buff_0x20[0xC];//0x20
    float z;//0x2c
};

#endif  // RASPTERNAL_DEFINITIONS_HPP
