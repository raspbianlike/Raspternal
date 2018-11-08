#include "Triggerbot.hpp"
#include "../SDK/CGlobalVars.hpp"

void Triggerbot::Run() {

    if (!enabled)
        return;

    if (localPlayer.entity.health < 1)
        return;

    crosshairIndex = 0;
    csgo.ReadBuffer(localPlayer.entityPtr + Offsets.localPlayer.crosshairID, &crosshairIndex, sizeof(int));

    if (crosshairIndex == 0 || crosshairIndex > globalVars.maxClients)
        return;

    EntityInfo *ent = &entities[crosshairIndex];

    if (!ent->entityPtr || ent->entityPtr == localPlayer.entityPtr || ent->entity.dormant || ent->entity.teamNum == localPlayer.entity.teamNum || ent->entity.health < 1)
        return;

    if (mouse.IsButtonDown(0x4))
        xdo_click_window(xdo, CURRENTWINDOW, 1);
}


void Triggerbot::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Triggerbot has been ").append(enabled ? "enabled" : "disabled").c_str());
}