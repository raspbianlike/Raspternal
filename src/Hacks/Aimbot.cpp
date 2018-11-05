#include "Aimbot.hpp"
#include "../SDK/CGlobalVars.hpp"
#include "../SDK/definitions.hpp"
#include "../SDK/Input.hpp"
#include "../SDK/Engine.hpp"
#include "../SDK/BSPMap.hpp"
#include "../SDK/EntityList.hpp"
#include "../Helpers/Math.hpp"

Vector GetBone(uintptr_t studioBones, int bone) {
    BoneMatrix matrix;
    csgo.ReadBuffer(studioBones + bone * sizeof(BoneMatrix), &matrix, sizeof(BoneMatrix));
    return Vector(matrix.x, matrix.y, matrix.z);
}

void Aimbot::RCS(Vector& angle, Vector& viewAngle) {
    Vector aimPunch;
    csgo.ReadBuffer(localPlayer.entityPtr + Offsets.localPlayer.aimPunch, &aimPunch, sizeof(Vector));

    angle -= aimPunch * 2.0f;
    Aimbot::Smooth(angle, viewAngle, 1.3f);
}

void Aimbot::Smooth(Vector &angle, Vector &viewAngle, float val = 5.0f) {
    float factor = val;
    Vector delta = angle - viewAngle;
    delta.Normalize();
    Vector change;

    // perform angle change
    change = delta / factor;
    angle = viewAngle + change;
}

void Aimbot::Run() {
    // Update needed variables, maybe also make them global if needed in the future
    if ((!keyboard.IsButtonDown(KEY_V)) || !enabled)
        return;

    Vector pVecTarget = localPlayer.entity.absOrigin + localPlayer.entity.viewOffset;
    //Logger::Debug("Offset: (%f, %f, %f)", localPlayer.entity.viewOffset.x, localPlayer.entity.viewOffset.y, localPlayer.entity.viewOffset.z);

    //pVecTarget.z += localPlayer.entity.viewOffset.z;
    Vector eVecTarget; // Enemy (bone) position
    Vector viewAngles;
    engine.GetViewAngles(viewAngles);
    Vector aim; // angle we will be aiming at
    EntityInfo *target = nullptr; // our target entity
    float bestFov = 15.0f;
    Vector bestAim;
    // Iterate over all Entities until we find one that we can shoot

    for (int i = 1; i < globalVars.maxClients; i++) {
        EntityInfo *ent = &entities[i];
        if (!ent->entityPtr || ent->entity.dormant || ent->entity.health < 1 || ent->entity.teamNum == localPlayer.entity.teamNum || ent->entityPtr == localPlayer.entityPtr)
            continue;

        uintptr_t studioBones;
        csgo.ReadBuffer(ent->entityPtr + Offsets.entity.studioBones, &studioBones, sizeof(uintptr_t));

        eVecTarget = GetBone(studioBones, 8); // 8 = Head (probably)

        if (eVecTarget.x == 0 && eVecTarget.y == 0 && eVecTarget.z == 0) // check if we have invalid data
            continue;

        aim = Math::CalcAngle(pVecTarget, eVecTarget); // successfully found viable target
        float fov = Math::AngleFOV(viewAngles, aim);

        Math::Clamp(aim);

        if (fov > bestFov)
            continue;

        if (!bspMap.Visible(pVecTarget, eVecTarget))
            continue;

        bestAim = aim;
        target = &entities[i];
        bestFov = fov;
    }
    //Logger::Debug("Viewangles: (%f, %f, %f)", viewAngles.x, viewAngles.y, viewAngles.z);
    //Logger::Debug("Target Angle: (%f, %f, %f)", bestAim.x, bestAim.y, bestAim.z);
    //Logger::Debug("FOV: %f", bestFov);
    if (target) {
        //Logger::Debug("Found viable target! Viewangle: (%f, %f, %f), team: %i, locteam", aim.x, aim.y, aim.z, target->entity.teamNum, localPlayer.entity.teamNum);
        //RCS(bestAim, viewAngles);
        //Smooth(bestAim, viewAngles);
        Math::Clamp(bestAim);
        engine.SetViewAngles(bestAim);
    }
}

void Aimbot::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Aimbot has been ").append(enabled ? "enabled" : "disabled").c_str());
}
