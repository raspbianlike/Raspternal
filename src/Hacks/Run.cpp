#include "Run.hpp"
#include "../SDK/CGlobalVars.hpp"

Entity localPlayer{};
std::array<Entity, 64> entities{};
CGlobalVars globalVars{};
int previousTickCount = 0;
int previousFrameCount = 0;

void Run::Run() {
    while (true) {
        int tick = 0;
        int frame = 0;

        // Run hacks every frame
        csgo.ReadBuffer(Offsets::GlobalVars::globalVars + 0x4, &frame, sizeof(int));
        if (frame != previousFrameCount || previousFrameCount == 0) {
            // Update entities and such every tick
            csgo.ReadBuffer(Offsets::GlobalVars::globalVars + 0x1C, &tick, sizeof(int));
            if (tick != previousTickCount || previousTickCount == 0) {

                csgo.ReadBuffer(Offsets::GlobalVars::globalVars, &globalVars, sizeof(CGlobalVars));
                csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity));
                for (int i = 0; i < globalVars.maxClients; i++)
                    entities[i] = CBaseEntity::GetEntity(i);

                previousTickCount = tick;
            }

            // Run Hacks

            // Measure execution time of hacks

            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
            Hacks::Run();
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

            if (Misc::BHop::enabled) { // TODO: Make module for this
                //Logger::Debug("\"Hack\" CPU time: %i microseconds, %f ticks", duration, duration / 100.0f / (1000.0f * globalVars.interval_per_tick));
            }
            //Logger::Debug("Frametime: %f", globalVars.frametime);
            previousFrameCount = frame;
        }
        int frameMS = globalVars.frametime * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(frameMS - 1));
    }
}