#include "CBaseEntity.hpp"

Entity CBaseEntity::GetEntity(int index) {
    Entity temp;
    uintptr_t ptr;;
    csgo.ReadBuffer((Offsets::EntityList::entityListPointer + 8 + 32 * index), &ptr, sizeof(uintptr_t));
    csgo.ReadBuffer(ptr, &temp, sizeof(Entity));
    return temp;
}
