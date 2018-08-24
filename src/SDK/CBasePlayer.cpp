#include "CBasePlayer.hpp"

Entity CBasePlayer::GetEntity(int index) {
    Entity temp;
    uintptr_t ptr;
    csgo.ReadBuffer((uintptr_t) (32 * index + Offsets::EntityList::entityListPointer + 8), &ptr, sizeof(uintptr_t));
    Logger::Address("ptr", (32 * index + Offsets::EntityList::entityListPointer + 8));
    Logger::Address("localplayer", ptr);
    csgo.ReadBuffer(ptr, &temp, sizeof(Entity));
    return temp;
}
