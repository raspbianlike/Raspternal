#include "Run.hpp"
#include "../SDK/CGlobalVars.hpp"

Entity localPlayer{};
std::array<Entity, 64> entities{};
CGlobalVars globalVars{};
int previousTickCount = 0;

void Run::Run() {
    while (true) {
        int tick = 0;
        csgo.ReadBuffer(Offsets::GlobalVars::globalVars + 0x1C, &tick, sizeof(int));
        if (tick == previousTickCount)
            continue;

        previousTickCount = tick;

        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        memset(&localPlayer, NULL, sizeof(localPlayer));
        memset(&entities, NULL, sizeof(entities));
        memset(&globalVars, NULL, sizeof(globalVars));

        csgo.ReadBuffer(Offsets::GlobalVars::globalVars, &globalVars, sizeof(CGlobalVars));
        csgo.ReadBuffer(Offsets::GlobalVars::globalVars, &globalVars, sizeof(CGlobalVars));
        csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity));
        for (int i = 0; i < globalVars.maxClients; i++) // TODO: read out maxClients using globalVars
            entities[i] = CBaseEntity::GetEntity(i);

        // run hacks
        Hacks::Run();

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        float ticks = duration / 100.0f / globalVars.interval_per_tick;
        if (false) { // TODO: Make module for this
            Logger::Info("Run CPU time: %i microseconds, %f ticks", duration, ticks);
        }
    }
}