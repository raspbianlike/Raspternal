#include "Glow.hpp"

struct Glow::GlowObjectDefinition_t definitions[1024];
Glow::CGlowObjectManager manager;

void Glow::Run() {

    if (!enabled)
        return;

    memset(definitions, NULL, sizeof(definitions));
    memset(&manager, NULL, sizeof(manager));

    csgo.ReadBuffer(Offsets.glowManager.memoryAddress, &manager, sizeof(CGlowObjectManager));

    size_t c = manager.m_GlowObjectDefinitions.Count;
    csgo.ReadBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr, definitions, sizeof(GlowObjectDefinition_t) * c);

    for (size_t i = 0; i < c; i++) {
        if (!definitions[i].m_pEntity)
            continue;

        Entity ent;
        csgo.ReadBuffer((uintptr_t) definitions[i].m_pEntity, &ent, sizeof(Entity));

        if ((ent.teamNum != 2 && ent.teamNum != 3) || (uintptr_t) definitions[i].m_pEntity == localPlayer.entityPtr || ent.dormant) {
            continue;
        }
        std::array<float, 4> col = {0.0f, 1.0f, 0.0f, 1.0f};
        if (!ent.health)
            col = {1.0f, 1.0f, 1.0f, 1.0f};

        if (ent.teamNum == localPlayer.entity.teamNum && ent.health > 1)  // teammates blue
            col = {0.0f, 0.0f, 1.0f, 0.6f};
        else if (ent.health) { // enemies red / reen
            if (Triggerbot::crosshairIndex == ent.index)
                col = {0.0f, 1.0f, 0.0f, 0.6f};
            else
                col = {1.0f, 0.0f, 0.0f, 0.6f};
        }

        static bool render = true;
        static bool render2 = false;
        csgo.WriteBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr + i * sizeof(GlowObjectDefinition_t) + 0x8, &col, sizeof(float) * 4);
        csgo.WriteBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr + i * sizeof(GlowObjectDefinition_t) + 0x28, &render, sizeof(bool));
        csgo.WriteBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr + i * sizeof(GlowObjectDefinition_t) + 0x29, &render2, sizeof(bool));
        //csgo.WriteBuffer((uintptr_t) manager.m_GlowObjectDefinitions.DataPtr + i * sizeof(GlowObjectDefinition_t) + 0x2A, &render, sizeof(bool));

    }
}

void Glow::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Glow has been ").append(enabled ? "enabled" : "disabled").c_str());
}
