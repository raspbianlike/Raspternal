#include "Aimbot.hpp"

EntityInfo *locked;
long lockTime = Utils::GetEpochTime();

CSWeaponType activeWeapon;

Vector Aimbot::GetBonePosition(EntityInfo *player, int bone) {
    BoneMatrix matrix;
    uintptr_t studioBones;

    csgo.ReadBuffer(player->entityPtr + Offsets.entity.studioBones, &studioBones, sizeof(uintptr_t));

    csgo.ReadBuffer(studioBones + bone * sizeof(BoneMatrix), &matrix, sizeof(BoneMatrix));

    return Vector(matrix.x, matrix.y, matrix.z);;
}

void Aimbot::GetClosestBone(EntityInfo *target, QAngle &viewAngle, Vector &out) {
    bool bones[] = {false, false, false, false, false, true, true, true, true}; // TODO: Config

    const int loopSize = sizeof(bones) / sizeof(bones[0]);

    float tempFov = bestFov;

    Vector pVecTarget = localPlayer.entity.absOrigin + localPlayer.entity.viewOffset;

    QAngle tmpAngle;

    for (int i = 0; i < loopSize; i++) {
        if (!bones[i])
            continue;

        Vector tmpVec = GetBonePosition(target, i);
        tmpAngle = Math::CalcAngle(pVecTarget, tmpVec);

        float tmpFov = Math::AngleFOV(viewAngle, tmpAngle);

        if (tmpFov > tempFov)
            continue;

        tempFov = tmpFov;

        out = tmpVec;
    }
}

EntityInfo *Aimbot::GetClosestPlayer(QAngle &angle, QAngle &viewAngle) {

    Vector pVecTarget = localPlayer.entity.absOrigin + localPlayer.entity.viewOffset;

    Vector eVecTarget; // Enemy position

    EntityInfo *target = nullptr; // our target entity
    float workingFOV = bestFov;

    // Iterate over all Entities until we find one that we can shoot

    for (int i = 1; i < globalVars.maxClients; i++) {
        EntityInfo *ent = &entities[i];

        if (!ent->entityPtr || ent->entity.dormant || ent->entity.health < 1 || ent->entity.teamNum == localPlayer.entity.teamNum || ent->entityPtr == localPlayer.entityPtr)
            continue;

        QAngle workingAngle = angle;
        QAngle workingView = viewAngle;

        AddRC(workingView); // add aim punch back before calculating fov

        GetClosestBone(ent, workingView, eVecTarget); // Gets closest bone to crosshair position

        if (eVecTarget.x == 0 && eVecTarget.y == 0 && eVecTarget.z == 0) // check if we have invalid data
            continue;


        workingAngle = Math::CalcAngle(pVecTarget, eVecTarget); // found viable target

        float fov = Math::AngleFOV(workingView, workingAngle); // calculate absolute fov

        Math::Clamp(workingAngle);

        if (fov > workingFOV)
            continue;

        if (!bspMap.Visible(pVecTarget, eVecTarget))
            continue;

        if (locked && ent->entityPtr != locked->entityPtr && Utils::GetEpochTime() - lockTime < 2000) {
            if (locked->entity.health < 1) {
                break;
            }
            continue;
        }

        target = &entities[i];
        angle = workingAngle;
        workingFOV = fov;
    }

    if (target)
        return &entities[target->entity.index];

    return nullptr;
}

int Aimbot::GetWeaponID(uintptr_t entityPtr) {
    int m_hActiveWeapon = 0;
    int activeWeapon = 0;

    csgo.ReadBuffer(entityPtr + Offsets.weapon.m_hActiveWeapon, &m_hActiveWeapon, sizeof(int));

    if (!m_hActiveWeapon)
        return 0;

    activeWeapon = m_hActiveWeapon & 0xFFF;


    int currentWeaponId = 0;

    EntityInfo weapon = entityList.GetEntityInfo(activeWeapon);

    if (!weapon.entityPtr)
        return 0;

    csgo.ReadBuffer(weapon.entityPtr + Offsets.weapon.m_AttributeManager + 0x60 + Offsets.weapon.m_iItemDefinitionIndex + 0x1A, &currentWeaponId, sizeof(int));

    if (currentWeaponId > 262200)
        currentWeaponId &= 0xFFF;

    return currentWeaponId;
}

void Aimbot::RCS(QAngle &angle, QAngle &viewAngle) {
    if (!shouldRCS)
        return;

    QAngle aimPunch;
    csgo.ReadBuffer(localPlayer.entityPtr + Offsets.localPlayer.aimPunch, &aimPunch, sizeof(Vector));

    angle -= aimPunch * 2.0f;
    Aimbot::Smooth(angle, viewAngle, 0.2f);
}

void Aimbot::AddRC(QAngle &angle) {
    if (!shouldRCS)
        return;

    QAngle aimPunch;
    csgo.ReadBuffer(localPlayer.entityPtr + Offsets.localPlayer.aimPunch, &aimPunch, sizeof(Vector));

    angle += aimPunch * 2.0f;
}

void Aimbot::Smooth(QAngle &angle, QAngle &viewAngle, float val = 0.75f) {
    QAngle delta = angle - viewAngle;
    Math::Clamp(delta);

    if (delta.Length() < 0.1f)
        return;

    QAngle change;

    val = std::min(0.99f, val);
    change = delta - (delta * val);

    if (delta.Length() < 1.5f) {
        float coeff = (1.0f - val) / delta.Length() * 3.5f;

        coeff = std::min(0.99f, coeff);

        change = delta * coeff;
    }

    angle = viewAngle + change;
}

void Aimbot::Run() {
    // Update needed variables, maybe also make them global if needed in the future

    if (!mouse.IsButtonDown(0x1) || !enabled) {
        if (locked) {
            locked = nullptr;
            //lockTime = Utils::GetEpochTime();
        }
        return;
    }

    if (localPlayer.entity.health < 1)
        return;


    int weaponID = GetWeaponID(localPlayer.entityPtr);
    if (!weaponID)
        return;

    activeWeapon = Utils::GetWeaponType(weaponID);

    if (activeWeapon == CSWeaponType::WEAPONTYPE_C4
        || activeWeapon == CSWeaponType::WEAPONTYPE_KNIFE
        || activeWeapon == CSWeaponType::WEAPONTYPE_GRENADE
        || activeWeapon == CSWeaponType::WEAPONTYPE_UNKNOWN)
        return;

    shouldRCS = (activeWeapon != CSWeaponType::WEAPONTYPE_SNIPER_RIFLE && activeWeapon != CSWeaponType::WEAPONTYPE_PISTOL);

    QAngle bestAim, viewAngles;
    engine.GetViewAngles(viewAngles);

    EntityInfo *target = GetClosestPlayer(bestAim, viewAngles);

    if (!target || (bestAim.x == 0 && bestAim.y == 0 && bestAim.z == 0))
        return;

    RCS(bestAim, viewAngles);
    Smooth(bestAim, viewAngles);
    Math::Clamp(bestAim);
    engine.SetViewAngles(bestAim);

    locked = target;
    lockTime = Utils::GetEpochTime();
}

void Aimbot::Enable() {
    enabled = !enabled;
    Logger::Info(std::string("Aimbot has been ").append(enabled ? "enabled" : "disabled").c_str());
}
