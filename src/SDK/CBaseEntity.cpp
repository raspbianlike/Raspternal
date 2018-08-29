#include "CBaseEntity.hpp"

Entity CBaseEntity::GetEntity(int index) {
    Entity temp;
    uintptr_t ptr;
    csgo.ReadBuffer((uintptr_t) (32 * index + Offsets::EntityList::entityListPointer + 8), &ptr, sizeof(uintptr_t));
    csgo.ReadBuffer(ptr, &temp, sizeof(Entity));
    return temp;
}
