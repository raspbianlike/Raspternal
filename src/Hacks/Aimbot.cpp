#include "Aimbot.hpp"
#include "../SDK/CGlobalVars.hpp"
#include "../SDK/definitions.hpp"
#include "../SDK/EntityList.hpp"
#include "../Helpers/Math.hpp"
#include "../SDK/Input.hpp"
#include "../SDK/Engine.hpp"
#include "../SDK/BSPMap.hpp"

Vector GetBone(uintptr_t studioBones, int bone) {
    BoneMatrix matrix;
    csgo.ReadBuffer(studioBones + bone * sizeof(BoneMatrix), &matrix, sizeof(BoneMatrix));
    Vector ret(matrix.x, matrix.y, matrix.z);
    return ret;
}

void Aimbot::Run() {
    // Update needed variables, maybe also make them global if needed in the future
    if(!mouse.IsButtonDown(0x1) || !enabled)
        return;
    Vector pVecTarget = localPlayer.entity.origin + localPlayer.entity.viewOffset;
    Vector eVecTarget; // Enemy (bone) position
    Vector viewAngles;
    Vector aimPunch ;
    csgo.ReadBuffer(localPlayer.entityPtr + Offsets::LocalPlayer::aimPunch, &aimPunch, sizeof(Vector));
    engine.GetViewAngles(viewAngles);
    Vector aim; // angle we will be aiming at
    EntityInfo *target = nullptr; // our target entity
    float bestFov = 3.0f;
    Vector bestAim;
    // Iterate over all Entities until we find one that we can shoot

    for (int i = 1; i < globalVars.maxClients; i++) {
        EntityInfo *ent = &entities[i];
        if (!ent->entityPtr || ent->entity.dormant || ent->entity.health < 1 || ent->entity.teamNum < 2 || ent->entityPtr == localPlayer.entityPtr)
            continue;

        uintptr_t studioBones;
        csgo.ReadBuffer(ent->entityPtr + Offsets::Entity::studioBones, &studioBones, sizeof(uintptr_t));
        eVecTarget = GetBone(studioBones, 8); // 8 = Head (probably)
        if (eVecTarget.x == 0 && eVecTarget.y == 0 && eVecTarget.z == 0) // check if we have invalid data
            continue;

        aim = Math::CalcAngle(pVecTarget, eVecTarget); // successfully found viable target
        float fov = Math::AngleFOV(viewAngles, aim);
        //aim.Normalize();
        Math::Clamp(aim);
        if(fov > bestFov)
            continue;

        if(!bspMap.Visible(pVecTarget, eVecTarget))
            continue;
        bestAim = aim;
        target = &entities[i];
        bestFov = fov;
    }
    /*Logger::Debug("Viewangles: (%f, %f, %f)", viewAngles.x, viewAngles.y, viewAngles.z);
    Logger::Debug("Enemy Bone pos: (%f, %f, %f)", eVecTarget.x, eVecTarget.y, eVecTarget.z);
    Logger::Debug("FOV: %f", bestFov);
    Logger::Debug("Found viable target! Viewangle: (%f, %f, %f), index: %i", aim.x, aim.y, aim.z,target->entity.index);*/
    if(target) {
        bestAim -= aimPunch * 2.0f;
        engine.SetViewAngles(bestAim);
    }
}

void Aimbot::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Aimbot has been ").append(enabled ? "enabled" : "disabled").c_str());
}