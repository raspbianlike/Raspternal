#include "Run.hpp"
Entity localPlayer{};

void Run::Run() {
    while(true) {
        // update global stuff like entities, localplayer and such,sync it with globalvars

        memset(&localPlayer, NULL, sizeof(localPlayer));
        //memset(&entities, NULL, sizeof(entities));

        csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity));
       // csgo.ReadBuffer(Offsets::EntityList::entityListPointer + 8, &entities, sizeof(Entity) * 64);

        // run hacks

        Hacks::Run();
    }
}