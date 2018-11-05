#ifndef RASPTERNAL_CBASENTITY_HPP
#define RASPTERNAL_CBASENTITY_HPP

#include "definitions.hpp"
#include "SDK.hpp"

extern EntityInfo localPlayer;
extern std::array<EntityInfo, 64> entities;

class EntityList {
public:
    Entity GetEntity(int index) {
        Entity temp{};
        uintptr_t ptr;

        csgo.ReadBuffer(Offsets.entityList.entityListPointer + 8 + 32 * index, &ptr, sizeof(uintptr_t));
        if (ptr)
            csgo.ReadBuffer(ptr, &temp, sizeof(Entity));

        return temp;
    };

    EntityInfo GetEntityInfo(int index) {
        Entity temp{};
        uintptr_t ptr;

        csgo.ReadBuffer(Offsets.entityList.entityListPointer + 8 + 32 * index, &ptr, sizeof(uintptr_t));
        if (ptr) {
            csgo.ReadBuffer(ptr, &temp, sizeof(Entity));
            return EntityInfo{temp, ptr};
        }
        return EntityInfo{};
    };
};

inline EntityList entityList;
#endif //RASPTERNAL_C_BASENTITY_HPP
