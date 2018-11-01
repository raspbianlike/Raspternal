#include "Aimbot.hpp"
#include "../SDK/CGlobalVars.hpp"
#include "../SDK/definitions.hpp"
#include "../SDK/EntityList.hpp"
#include "../Helpers/Math.hpp"

Vector GetBone(uintptr_t studioBones, int bone) {
    BoneMatrix matrix;
    csgo.ReadBuffer(studioBones + bone * sizeof(BoneMatrix), &matrix, sizeof(BoneMatrix));
    Vector ret(matrix.x, matrix.y, matrix.z);
    return ret;
}

void Aimbot::Run() {
    // Update needed variables, maybe also make them global if needed in the future
    Vector pVecTarget = localPlayer.entity.origin + localPlayer.entity.viewOffset;
    Vector eVecTarget; // Enemy (bone) position
    Vector aim; // angle we will be aiming at
    EntityInfo *target; // our target entity

    // Iterate over all Entities until we find one that we can shoot

    for (int i = 1; i < globalVars.maxClients; i++) {
        EntityInfo *ent = &entities[i];
        if (!ent->entityPtr || ent->entity.dormant || ent->entity.health < 0 || ent->entity.teamNum < 2 || ent->entityPtr == localPlayer.entityPtr)
            continue;

        uintptr_t studioBones;
        csgo.ReadBuffer(ent->entityPtr + Offsets::Entity::studioBones, &studioBones, sizeof(uintptr_t));
        eVecTarget = GetBone(studioBones, 1); // 1 = Head (probably)
        if (eVecTarget.x == 0 && eVecTarget.y == 0 && eVecTarget.z == 0) // check if we have invalid data
            continue;

        aim = Math::CalcAngle(&pVecTarget, &eVecTarget); // successfully found viable target
        //aim.Normalize();
        Math::Clamp(aim);
        target = &entities[i];
        Logger::Debug("Enemy Bone pos: (%f, %f, %f)", eVecTarget.x, eVecTarget.y, eVecTarget.z);
        Logger::Debug("FOV: %f", Math::AngleFOV(aim, aim));
        Logger::Debug("Found viable target! Viewangle: (%f, %f, %f)", aim.x, aim.y, aim.z);
        break;
    }
}

void Aimbot::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Aimbot has been ").append(enabled ? "enabled" : "disabled").c_str());
}