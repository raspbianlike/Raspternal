#include <WinTypes.h>
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
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    int ct = 0;
    while (true) {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        if (!engine.IsInGame()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        if (!bspMap.hasInit) {
            bspMap.hasInit = bspMap.load(csgo.processPath);
        }

        globalVars.UpdateGlobalVars();
        int tick = globalVars.tickcount;
        int frame = globalVars.framecount;


        if (frame == previousFrameCount) {
            float fframeTimeMs = globalVars.frametime * 1000.0f;
            int frameTimeMs = (int) fframeTimeMs;
            //printf("pre %i\n",frameTimeMs);
            frameTimeMs /= 3;
            //printf("af %i\n",frameTimeMs);
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            continue;
        }

        if (tick != previousTickCount) {
            localPlayer = entityList.GetEntityInfo(engine.GetLocalPlayer());

            for (int i = 0; i < globalVars.maxClients; i++)
                entities[i] = entityList.GetEntityInfo(i);

            previousTickCount = tick;
            ct++;
        }

        Hacks::Run();
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        if (duration >= 1000) {
            start = std::chrono::high_resolution_clock::now();

            float fps = (1000.0f / dur);

            fps *= 1000.0f;

            //Logger::Info("CPU time: %i microseconds, FPS: %f", dur, fps);
            ct = 0;
        }
        previousFrameCount = frame;
    }
}