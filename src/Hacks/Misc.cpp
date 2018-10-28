#include "Misc.hpp"

Entity localPlayer;


void Misc::NoFlash::Run() {
    static float maxFlashAmount = 70.0f;
    static float writeAmount = maxFlashAmount;
    float flash;

    if(!enabled)
        return;

    csgo.ReadBuffer(Offsets::LocalPlayer::instance + 0xABE8, &flash, sizeof(float)); // this is some sort of "time" that goes from 255 to 0 when flashed, i dont really know

    if (flash <= 0.1f) {
        return;
    }

    writeAmount = maxFlashAmount;
    if (flash <= maxFlashAmount) {
        writeAmount = flash;
    }

    csgo.WriteBuffer(Offsets::LocalPlayer::instance + Offsets::LocalPlayer::flash, &writeAmount, sizeof(float));
}

void Misc::NoFlash::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("NoFlash has been ").append(enabled ? "enabled" : "disabled").c_str());
}

void Misc::BHop::Run() {
    static int jump = 6;

    if(!enabled)
        return;

    if (keyboard.IsButtonDown(KEY_SPACE)) { // might want to add a check if the cursor is enabled, but were fine for now
        memset(&localPlayer, NULL, sizeof(Entity));
        csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity));
        if (localPlayer.flags == 257) {
            csgo.WriteBuffer(Offsets::Jump::IN_JUMP, &jump, sizeof(int));
            return;
        }
    }
}

void Misc::BHop::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("BHop has been ").append(enabled ? "enabled" : "disabled").c_str());
}
