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

        for (int i = 0; i < c; i++) {
            if (!definitions[i].m_pEntity)
                continue;

            Entity ent;
            if (!csgo.ReadBuffer((uintptr_t) definitions[i].m_pEntity, &ent,
                                 sizeof(Entity))) // could basically be used as a temporary entitylist replacement until entitylist is implemented
                continue;

            if (ent.health < 1 || (ent.teamNum != 2 && ent.teamNum != 3)) { // check if entity belongs to players 'and' if its a player, can also draw weapons n shit with this
                definitions[i].m_bRenderWhenOccluded = false;
                definitions[i].m_bRenderWhenUnoccluded = false;
                continue;
            }

            /*if (ent.health < 1 && !ent.teamNum) { // draw weapons white
                definitions[i].r = 1.0f;
                definitions[i].g = 1.0f;
                definitions[i].b = 1.0f;
                definitions[i].a = 1.0f;
                definitions[i].m_bRenderWhenOccluded = 1;
                definitions[i].m_bRenderWhenUnoccluded = 1;
            }
            else */
            if (definitions[i].m_bRenderWhenOccluded) // dont set stuff again
                continue;

            if (ent.teamNum == localPlayer.teamNum) { // teammates blue
                definitions[i].b = 1.0f;
                definitions[i].a = 1.0f;
                definitions[i].m_bRenderWhenOccluded = true;
                definitions[i].m_bRenderWhenUnoccluded = false;
            } else { // enemies red
                if (Triggerbot::crosshairIndex == ent.index) {
                    definitions[i].g = 1.0f;
                    definitions[i].a = 1.0f;
                } else {
                    definitions[i].r = 1.0f;
                    definitions[i].a = 1.0f;
                }
                definitions[i].m_bRenderWhenOccluded = true;
                definitions[i].m_bRenderWhenUnoccluded = false;
            }
        }
        csgo.WriteBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr, definitions, sizeof(GlowObjectDefinition_t) * c); // same as above
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