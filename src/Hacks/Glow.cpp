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
        csgo.ReadBuffer(Offsets::LocalPlayer::instance, &localPlayer, sizeof(Entity));

        for (int i = 0; i < manager.m_GlowObjectDefinitions.Count; i++) {
            if (!definitions[i].m_pEntity)
                continue;

            Entity ent;
            csgo.ReadBuffer((uintptr_t) definitions[i].m_pEntity, &ent,
                            sizeof(Entity)); // could basically be used as a temporary entitylist replacement until entitylist is implemented
            if (ent.health < 1)
                continue;

            if (ent.teamNum == localPlayer.teamNum) { // draw teammates blue
                definitions[i].m_flGlowBlue = 1.0f;
                definitions[i].m_flGlowAlpha = 1.0f;
                definitions[i].m_bRenderWhenOccluded = 1;
            } else { // enemies red
                definitions[i].m_flGlowRed = 1.0f;
                definitions[i].m_flGlowAlpha = 1.0f;
                definitions[i].m_bRenderWhenOccluded = 1;
            }
            //printf("Entity pointer: %p\n", definitions[i].m_pEntity);
        }
        csgo.WriteBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr, &definitions, sizeof(definitions));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Glow::Start() {
    pthread_create(&glow, nullptr, Run, nullptr);
}