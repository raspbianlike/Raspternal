#include "BHop.hpp"

Entity localPlayer;

void *BHop::Run(void *) {
    static int jump = 6;
    for (;;) {

        /*
         *
         * Basically reading from memory is faster than the X11 keycheck function, so we will want to get around that asap!
         *
         */

        // Update localPlayer;
        bzero(&localPlayer, sizeof(Entity));
        if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity)))
            continue;

        if (localPlayer.flags != 257) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }

        if (KeyCheck::IsButtonDown(XK_space)) // might want to add a check if the cursor is enabled, but were fine for now
            csgo.WriteBuffer(Offsets::Jump::IN_JUMP, &jump, sizeof(int));

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void BHop::Start() {
    if (!BHop::enabled)
        pthread_create(&bhop, nullptr, Run, nullptr);
    else {
        Logger::Error("BHop is already enabled!");
        return;
    }
    Logger::Info("BHop has been enabled!");
    BHop::enabled = true;
}

void BHop::Stop() {
    if (BHop::enabled)
        pthread_cancel(bhop);
    else {
        Logger::Error("BHop is already disabled!");
        return;
    }
    Logger::Info("BHop has been disabled");
    BHop::enabled = false;
}