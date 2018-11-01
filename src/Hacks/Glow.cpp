#include "Glow.hpp"

struct Glow::GlowObjectDefinition_t definitions[1024];
Glow::CGlowObjectManager manager;

void Glow::Run() {

    if (!enabled)
        return;

    memset(definitions, NULL, sizeof(definitions));
    memset(&manager, NULL, sizeof(manager));

    csgo.ReadBuffer(Offsets::GlowManager::memoryAddress, &manager, sizeof(CGlowObjectManager));

    size_t c = manager.m_GlowObjectDefinitions.Count;
    csgo.ReadBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr, definitions, sizeof(GlowObjectDefinition_t) * c);

    for (size_t i = 0; i < c; i++) {
        if (!definitions[i].m_pEntity)
            continue;

        Entity ent;
        csgo.ReadBuffer((uintptr_t) definitions[i].m_pEntity, &ent, sizeof(Entity));

        if ((ent.teamNum != 2 && ent.teamNum != 3) || (uintptr_t) definitions[i].m_pEntity == Offsets::LocalPlayer::instance || ent.dormant) {
            continue;
        }
        std::array<float, 4> col = {0.0f, 1.0f, 0.0f, 1.0f};
        if (!ent.health)
            col = {1.0f, 1.0f, 1.0f, 1.0f};

        if (ent.teamNum == localPlayer.entity.teamNum && ent.health)  // teammates blue
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
}

/*
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
}*/

void Glow::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Glow has been ").append(enabled ? "enabled" : "disabled").c_str());
}