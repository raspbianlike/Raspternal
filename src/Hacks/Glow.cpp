#include "Glow.hpp"

Glow::GlowObjectDefinition_t definitions[1024];

void *Glow::Run(void *) {
    for (;;) {
        Glow::CGlowObjectManager manager;
        bzero(definitions, sizeof(definitions));

        if (!csgo.ReadBuffer(Offsets::GlowManager::memoryAddress, &manager, sizeof(manager)))
            Logger::Error("Failed reading stuff!");

        if (!csgo.ReadBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr, &definitions, sizeof(definitions)))
            Logger::Error("Failed reading stuff!");

        // update localplayer;
        Entity localPlayer;
        if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity)))
            continue;
        //if (!csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity)))
        //    continue;

        for (int i = 1; i < manager.m_GlowObjectDefinitions.Count; i++) {
            if (!definitions[i].m_pEntity)
                continue;

            Entity ent;
            if (!csgo.ReadBuffer((uintptr_t) definitions[i].m_pEntity, &ent,
                                 sizeof(Entity))) // could basically be used as a temporary entitylist replacement until entitylist is implemented
                continue;

            if (ent.health < 1)
                continue;

            /*if (ent.health < 1 && !ent.teamNum) { // draw weapons white
                definitions[i].r = 1.0f;
                definitions[i].g = 1.0f;
                definitions[i].b = 1.0f;
                definitions[i].a = 1.0f;
                definitions[i].m_bRenderWhenOccluded = 1;
                definitions[i].m_bRenderWhenUnoccluded = 1;
            }
            else */
            if (ent.teamNum == localPlayer.teamNum) { // teammates blue
                definitions[i].b = 1.0f;
                definitions[i].a = 1.0f;
                definitions[i].m_bRenderWhenOccluded = 1;
                definitions[i].m_bRenderWhenUnoccluded = 0;
            } else { // enemies red
                definitions[i].r = 1.0f;
                definitions[i].a = 1.0f;
                definitions[i].m_bRenderWhenOccluded = 1;
                definitions[i].m_bRenderWhenUnoccluded = 0;
            }
        }
        csgo.WriteBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr, &definitions, sizeof(definitions));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Glow::Start() {
    if (!Glow::enabled)
        pthread_create(&glow, nullptr, Run, nullptr); // maybe switch to std::thread?
    else {
        Logger::Error("Glow is already enabled!");
        return;
    }
    Logger::Info("Glow has been enabled!");
    Glow::enabled = true;
}

void Glow::Stop() {
    if (Glow::enabled)
        pthread_cancel(glow);
    else {
        Logger::Error("Glow is already disabled!");
        return;
    }
    Logger::Info("Glow has been disabled!");
    Glow::enabled = false;
}