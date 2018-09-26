#include "Glow.hpp"

struct Glow::GlowObjectDefinition_t definitions[1024];
Glow::CGlowObjectManager manager;

void *Glow::Run(void *) {
    for (;;) {
        memset(definitions, NULL, sizeof(definitions));
        memset(&manager, NULL, sizeof(manager));

        if (!csgo.ReadBuffer(Offsets::GlowManager::memoryAddress, &manager, sizeof(CGlowObjectManager))) {
            Logger::Error("Failed reading stuff!");
            continue;
        }
        size_t c = manager.m_GlowObjectDefinitions.Count;
        if (!csgo.ReadBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr, definitions,
                             sizeof(GlowObjectDefinition_t) * c)) { // prevent to read more data than there actually is
            Logger::Error("Failed reading stuff!");
            continue;
        }
        // update localplayer;
        Entity localPlayer;
        if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity)))
            continue;
        //if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity)))
        //    continue;

        for (size_t i = 0; i < c; i++) {
            if (!definitions[i].m_pEntity)
                continue;

            Entity ent;
            if (!csgo.ReadBuffer((uintptr_t) definitions[i].m_pEntity, &ent, sizeof(Entity)))
                continue;

            if ((ent.teamNum != 2 && ent.teamNum != 3) || (uintptr_t) definitions[i].m_pEntity == Offsets::LocalPlayer::instance || ent.dormant) {
                continue;
            }
            std::array<float, 4> col = {0.0f, 1.0f, 0.0f, 1.0f};
            if (!ent.health)
                col = {1.0f, 1.0f, 1.0f, 1.0f};

            if (ent.teamNum == localPlayer.teamNum && ent.health)  // teammates blue
                col = {0.0f, 0.0f, 1.0f, 1.0f};
            else if (ent.health) { // enemies red / reen
                if (Triggerbot::crosshairIndex == ent.index)
                    col = {0.0f, 1.0f, 0.0f, 1.0f};
                else
                    col = {1.0f, 0.0f, 0.0f, 1.0f};
            }

            static bool render = true;
            csgo.WriteBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr + i * sizeof(GlowObjectDefinition_t) + 0x8, &col, sizeof(float) * 4);
            csgo.WriteBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr + i * sizeof(GlowObjectDefinition_t) + 0x28, &render, sizeof(bool));

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Glow::Start() {
    if (!enabled)
        pthread_create(&glow, nullptr, Run, nullptr); // maybe switch to std::thread?
    else {
        Logger::Error("Glow is already enabled!");
        return;
    }
    Logger::Info("Glow has been enabled!");
    enabled = true;
}

void Glow::Stop() {
    if (enabled)
        pthread_cancel(glow);
    else {
        Logger::Error("Glow is already disabled!");
        return;
    }
    Logger::Info("Glow has been disabled!");
    enabled = false;
}