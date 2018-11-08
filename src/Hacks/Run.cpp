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
            frameTimeMs /= 4;
            std::this_thread::sleep_for(std::chrono::microseconds(frameTimeMs));
            continue;
        }

        if (tick != previousTickCount) {
            localPlayer.entityPtr = Offsets.localPlayer.instance;
            csgo.ReadBuffer(localPlayer.entityPtr, &localPlayer.entity, sizeof(Entity));

            for (int i = 0; i < globalVars.maxClients; i++)
                entities[i] = entityList.GetEntityInfo(i);
            previousTickCount = tick;
            ct++;
        }

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (duration >= 1000) {
            start = std::chrono::high_resolution_clock::now();
            //Logger::Info("CT: %i", ct);
            ct = 0;
        }
        Hacks::Run();
        previousFrameCount = frame;
    }
}