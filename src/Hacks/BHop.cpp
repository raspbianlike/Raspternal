#include "BHop.hpp"

Entity localPlayer;

void *BHop::Run(void *) {
    static int jump = 6;
    for (;;) {
        if (keyboard.IsButtonDown(KEY_SPACE)) { // might want to add a check if the cursor is enabled, but were fine for now
            memset(&localPlayer, NULL, sizeof(Entity));
            csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity));
            if (localPlayer.flags == 257) {
                csgo.WriteBuffer(Offsets::Jump::IN_JUMP, &jump, sizeof(int));
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // TODO: only run hacks every network update
                continue;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void BHop::Start() {
    if (!enabled)
        pthread_create(&bhop, nullptr, Run, nullptr);
    else {
        Logger::Error("BHop is already enabled!");
        return;
    }
    Logger::Info("BHop has been enabled!");
    enabled = true;
}

void BHop::Stop() {
    if (enabled)
        pthread_cancel(bhop);
    else {
        Logger::Error("BHop is already disabled!");
        return;
    }
    Logger::Info("BHop has been disabled!");
    enabled = false;
}