#ifndef RASPTERNAL_CBASENTITY_HPP
#define RASPTERNAL_CBASENTITY_HPP

#include "Entity.hpp"
#include "SDK.hpp"

extern Entity localPlayer;
extern std::array<Entity, 64> entities;

namespace CBaseEntity {
    inline Entity GetEntity(int index) {
        Entity temp{};
        uintptr_t ptr;

        csgo.ReadBuffer((Offsets::EntityList::entityListPointer + 8 + 32 * index), &ptr, sizeof(uintptr_t));
        if (ptr)
            csgo.ReadBuffer(ptr, &temp, sizeof(Entity));

        return temp;
    };
}


#endif //RASPTERNAL_C_BASENTITY_HPP
