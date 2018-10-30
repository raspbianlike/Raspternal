#include "Triggerbot.hpp"

void Triggerbot::Run() {

    if (!enabled)
        return;

    if (localPlayer.health < 1)
        return;

    csgo.ReadBuffer(Offsets::LocalPlayer::instance + Offsets::LocalPlayer::crosshairID, &crosshairIndex, sizeof(int));
    if (crosshairIndex == 0)
        return;

    Entity ent = entities[crosshairIndex];

    if (ent.dormant || ent.teamNum == localPlayer.teamNum)
        return;

    if (keyboard.IsButtonDown(KEY_LEFTALT))
        xdo_click_window(xdo, CURRENTWINDOW, 1);
}


void Triggerbot::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Triggerbot has been ").append(enabled ? "enabled" : "disabled").c_str());
}