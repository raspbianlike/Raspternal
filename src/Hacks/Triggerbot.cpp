#include "Triggerbot.hpp"

void Triggerbot::Run() {
        // update localPlayer;

        if(!enabled)
            return;

        Entity localPlayer;
        if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity)))
            std::exit(-1);
        //printf("%i\n", localPlayer.index);
        if (localPlayer.health < 1) { // localplayer dead, sleep for 500 ms
            return;
        }

        if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance + Offsets::LocalPlayer::crosshairID, &crosshairIndex, sizeof(int)))
            std::exit(-1);

        if (crosshairIndex == 0) { // not aiming onto any player, continue
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            std::exit(-1);
        }

        Entity ent = CBaseEntity::GetEntity(crosshairIndex);

        if (ent.teamNum == localPlayer.teamNum)
            return;

        if (keyboard.IsButtonDown(KEY_MENU))
            xdo_click_window(xdo, CURRENTWINDOW, 1);
    }


void Triggerbot::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Triggerbot has been ").append(enabled ? "enabled" : "disabled").c_str());
}