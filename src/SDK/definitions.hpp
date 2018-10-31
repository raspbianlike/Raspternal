#ifndef RASPTERNAL_DEFINITIONS_HPP
#define RASPTERNAL_DEFINITIONS_HPP

struct Entity {
    char pad[0x94]; // 0x0
    int index; // 0x94
    char pad4[0x89]; // 0x98
    bool dormant; //  0x121
    char pad5[0x6]; // 0x122
    int teamNum; // 0x128
    char pad2[0x8]; // 0x12C
    int health; // 0x134
    int flags; // 0x138
    char pad3[0x30]; // 0x13C
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
