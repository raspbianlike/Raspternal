#include "Run.hpp"
#include "../SDK/CGlobalVars.hpp"
#include "../SDK/Engine.hpp"
#include "../SDK/BSPMap.hpp"

EntityInfo localPlayer{};
std::array<EntityInfo, 64> entities{};
CGlobalVars globalVars{};
int previousTickCount = 0;
int previousFrameCount = 0;

void Run::Run() {
    while (true) {

        if(!engine.IsInGame()) {
            bspMap.hasInit = false;
            return;
        }

        if(!bspMap.hasInit) {
            bspMap.hasInit = bspMap.load(csgo.processPath);
            bspMap.DisplayInfo();
        }
        int tick = 0;
        int frame = 0;
        int clients = 0;

        // Run hacks every frame

        if (frame != previousFrameCount || previousFrameCount == 0) {
            // Update entities and such every tick
            csgo.ReadBuffer(Offsets::GlobalVars::globalVars + 0x1C, &tick, sizeof(int));
            if (tick != previousTickCount || previousTickCount == 0) {
                globalVars.UpdateGlobalVars();
                localPlayer = entityList.GetEntityInfo(1); // TODO: Find out how to get static localplayer index
                for (int i = 0; i < globalVars.maxClients; i++)
                    entities[i] = entityList.GetEntityInfo(i);

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