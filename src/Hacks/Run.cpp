#include "Run.hpp"

Entity localPlayer{};
std::array<Entity, 64> entities{};

void Run::Run() {
    while (true) {
        // update global stuff like entities, localplayer and such, sync it with globalvars
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        memset(&localPlayer, NULL, sizeof(localPlayer));
        memset(&entities, NULL, sizeof(entities));

        csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity));
        for (int i = 0; i < 64; i++) // TODO: read out maxClients using globalVars
            entities[i] = CBaseEntity::GetEntity(i);

        // run hacks
        Hacks::Run();

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        float ticks = duration / 100.0f / (1000.0f / 64.0f); // todo:: globalvars interval per tick
        if (false) { // TODO: Make module for this
            Logger::Info("Run CPU time: %i microseconds, %f ticks", duration, ticks);
        }
    }
}