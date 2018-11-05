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
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return;
        }

        if(!bspMap.hasInit) {
            bspMap.hasInit = bspMap.load(csgo.processPath);
        }

        int tick = 0;
        int frame = 0;

        // Run hacks every frame
        csgo.ReadBuffer(Offsets.globalVars.globalVars + 0x4, &frame, sizeof(int));
        if (frame != previousFrameCount || previousFrameCount == 0 ) {
            // Update entities and such every tick
            csgo.ReadBuffer(Offsets.globalVars.globalVars + 0x1C, &tick, sizeof(int));
            if (tick != previousTickCount || previousTickCount == 0) {
                globalVars.UpdateGlobalVars();
                //localPlayer = entityList.GetEntityInfo(1); // TODO: Find out how to get static localplayer index (done already)
                csgo.ReadBuffer(Offsets.localPlayer.instance, &localPlayer.entity, sizeof(Entity));
                localPlayer.entityPtr = Offsets.localPlayer.instance;
                for (int i = 0; i < globalVars.maxClients; i++)
                    entities[i] = entityList.GetEntityInfo(i);

                previousTickCount = tick;
            }

            // Run Hacks
            Hacks::Run();

            previousFrameCount = frame;

        }
        else {
            int frameMS = (int)globalVars.frametime;
            std::this_thread::sleep_for(std::chrono::milliseconds(frameMS));
        }
    }
}