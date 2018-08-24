#include "Triggerbot.hpp"

extern "C" {
#include <xdo.h>
}
static xdo_t *xdo = xdo_new(NULL);

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

        int crosshairIndex = 0;
        if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance + Offsets::LocalPlayer::crosshairID, &crosshairIndex, sizeof(int)))
            continue;

        if (crosshairIndex == 0) { // not aiming to any player, continue
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }
        if (KeyCheck::IsButtonDown(XK_Alt_L))
            xdo_click_window(xdo, CURRENTWINDOW, 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

void Triggerbot::Start() {
    if (!Triggerbot::enabled)
        pthread_create(&triggerbot, nullptr, Run, nullptr);
}

void Triggerbot::Stop() {

}