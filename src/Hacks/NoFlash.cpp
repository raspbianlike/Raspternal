#include "NoFlash.hpp"

void *NoFlash::Run(void *) {
    for (;;) {
        static float maxFlashAmount = 70.0f;
        static float writeAmount = maxFlashAmount;
        float flash;

        csgo.ReadBuffer(Offsets::LocalPlayer::instance + 0xABE8, &flash, sizeof(float)); // this is some sort of "time" that goes from 255 to 0 when flashed, i dont really know

        if (flash <= 0.1f) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        writeAmount = maxFlashAmount;
        if (flash <= maxFlashAmount) {
            writeAmount = flash;
        }

        csgo.WriteBuffer(Offsets::LocalPlayer::instance + Offsets::LocalPlayer::flash, &writeAmount, sizeof(float));

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void NoFlash::Start() {
    if (!enabled)
        pthread_create(&noflash, nullptr, Run, nullptr);
    else {
        Logger::Error("Noflash is already enabled!");
        return;
    }
    Logger::Info("NoFlash has been enabled!");
    enabled = true;
}

void NoFlash::Stop() {
    if (enabled)
        pthread_cancel(noflash);
    else {
        Logger::Error("Noflash is already disabled!");
        return;
    }
    Logger::Info("NoFlash has been disabled!");
    enabled = false;
}