#include "Triggerbot.hpp"
#include "../SDK/CGlobalVars.hpp"

void Triggerbot::Run() {

    if (!enabled)
        return;

    if (localPlayer.entity.health < 1)
        return;

    crosshairIndex = 0;
    csgo.ReadBuffer(Offsets::LocalPlayer::instance + Offsets::LocalPlayer::crosshairID, &crosshairIndex, sizeof(int));

    if (crosshairIndex == 0 || crosshairIndex > globalVars.maxClients)
        return;

    EntityInfo *ent = &entities[crosshairIndex];

    if (!ent->entityPtr || ent->entityPtr == localPlayer.entityPtr || ent->entity.dormant || ent->entity.teamNum == localPlayer.entity.teamNum || ent->entity.health < 1)
        return;

    if (keyboard.IsButtonDown(KEY_LEFTALT))
        xdo_click_window(xdo, CURRENTWINDOW, 1);
}


void Triggerbot::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Triggerbot has been ").append(enabled ? "enabled" : "disabled").c_str());
}