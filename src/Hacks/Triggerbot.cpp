#include "Triggerbot.hpp"

void *Triggerbot::Run(void *) {
    for (;;) {
        // update localPlayer;
        Entity localPlayer;
        if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity)))
            continue;
        //printf("%i\n", localPlayer.index);
        if (localPlayer.health < 1) { // localplayer dead, sleep for 500 ms
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance + Offsets::LocalPlayer::crosshairID, &crosshairIndex, sizeof(int)))
            continue;

        if (crosshairIndex == 0) { // not aiming onto any player, continue
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            continue;
        }

        Entity ent = CBaseEntity::GetEntity(crosshairIndex);

        if (ent.teamNum == localPlayer.teamNum)
            continue;

        if (KeyCheck::IsButtonDown(XK_Alt_L))
            xdo_click_window(xdo, CURRENTWINDOW, 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

void Triggerbot::Start() {
    if (!enabled)
        pthread_create(&triggerbot, nullptr, Run, nullptr);
    else {
        Logger::Error("Triggerbot is already enabled!");
        return;
    }
    //Logger::Info("Triggerbot is currently in maintance!");
    Logger::Info("Triggerbot has been enabled!");
    enabled = true;
}


void Triggerbot::Stop() {
    if (enabled)
        pthread_cancel(Triggerbot::triggerbot);
    else {
        Logger::Error("Triggerbot is already disabled!");
        return;
    }
    Logger::Info("Triggerbot has been disabled!");
    enabled = false;
}