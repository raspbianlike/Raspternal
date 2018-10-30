#include "Run.hpp"

Entity localPlayer{};
std::array<Entity, 64> entities{};

void Run::Run() {
    while (true) {
        // update global stuff like entities, localplayer and such, sync it with globalvars

        memset(&localPlayer, NULL, sizeof(localPlayer));
        memset(&entities, NULL, sizeof(entities));

        csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity));
        for (int i = 0; i < 64; i++) // TODO: read out maxClients using globalVars
            entities[i] = CBaseEntity::GetEntity(i);

        // run hacks

        Hacks::Run();
    }
}