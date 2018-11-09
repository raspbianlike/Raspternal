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

enum WeaponIndex {
    WEAPON_NONE,
    WEAPON_DEAGLE = 1,
    WEAPON_ELITE = 2,
    WEAPON_FIVESEVEN = 3,
    WEAPON_GLOCK = 4,
    WEAPON_AK47 = 7,
    WEAPON_AUG = 8,
    WEAPON_AWP = 9,
    WEAPON_FAMAS = 10,
    WEAPON_G3SG1 = 11,
    WEAPON_GALILAR = 13,
    WEAPON_M249 = 14,
    WEAPON_M4A1 = 16,
    WEAPON_MAC10 = 17,
    WEAPON_P90 = 19,
    WEAPON_UMP45 = 24,
    WEAPON_XM1014 = 25,
    WEAPON_BIZON = 26,
    WEAPON_MAG7 = 27,
    WEAPON_NEGEV = 28,
    WEAPON_SAWEDOFF = 29,
    WEAPON_TEC9 = 30,
    WEAPON_TASER = 31,
    WEAPON_HKP2000 = 32,
    WEAPON_MP7 = 33,
    WEAPON_MP9 = 34,
    WEAPON_NOVA = 35,
    WEAPON_P250 = 36,
    WEAPON_SCAR20 = 38,
    WEAPON_SG556 = 39,
    WEAPON_SSG08 = 40,
    WEAPON_KNIFE = 42,
    WEAPON_FLASHBANG = 43,
    WEAPON_HEGRENADE = 44,
    WEAPON_SMOKEGRENADE = 45,
    WEAPON_MOLOTOV = 46,
    WEAPON_DECOY = 47,
    WEAPON_INCGRENADE = 48,
    WEAPON_C4 = 49,
    WEAPON_KNIFE_T = 59,
    WEAPON_M4A1_SILENCER = 60,
    WEAPON_USP_SILENCER = 61,
    WEAPON_CZ75A = 63,
    WEAPON_REVOLVER = 64,
    WEAPON_KNIFE_BAYONET = 500,
    WEAPON_KNIFE_FLIP = 505,
    WEAPON_KNIFE_GUT = 506,
    WEAPON_KNIFE_KARAMBIT = 507,
    WEAPON_KNIFE_M9_BAYONET = 508,
    WEAPON_KNIFE_TACTICAL = 509,
    WEAPON_KNIFE_FALCHION = 512,
    WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
    WEAPON_KNIFE_BUTTERFLY = 515,
    WEAPON_KNIFE_PUSH = 516,
    WEAPON_MAX
};

enum CSWeaponType {
    WEAPONTYPE_KNIFE = 0,
    WEAPONTYPE_PISTOL,
    WEAPONTYPE_SUBMACHINEGUN,
    WEAPONTYPE_RIFLE,
    WEAPONTYPE_SHOTGUN,
    WEAPONTYPE_SNIPER_RIFLE,
    WEAPONTYPE_MACHINEGUN,
    WEAPONTYPE_C4,
    WEAPONTYPE_GRENADE,
    WEAPONTYPE_UNKNOWN

};

#endif  // RASPTERNAL_DEFINITIONS_HPP
