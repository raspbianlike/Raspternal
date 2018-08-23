#ifndef RASPTERNAL_ENTITY_HPP
#define RASPTERNAL_ENTITY_HPP

struct Entity {
    char pad[0x128]; // 0x0
    int teamNum; // 0x128
    char pad2[0x8]; // 0x12C
    int health; // 0x134
    int flags; // 0x138
    char pad3[0x30]; // 0x13C
};

#endif  // RASPTERNAL_ENTITY_HPP
