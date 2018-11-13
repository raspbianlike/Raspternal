#ifndef RASPTERNAL_AIMBOT_HPP
#define RASPTERNAL_AIMBOT_HPP

#include "../Helpers/Logger.hpp"
#include "../Helpers/Math.hpp"
#include "../Helpers/Utils.hpp"
#include "../SDK/Vector.hpp"
#include "../SDK/definitions.hpp"
#include "../SDK/CGlobalVars.hpp"
#include "../SDK/Input.hpp"
#include "../SDK/Engine.hpp"
#include "../SDK/BSPMap.hpp"
#include "../SDK/EntityList.hpp"


namespace Aimbot {

    Vector GetBonePosition(EntityInfo *player, int bone);

    void GetClosestBone(EntityInfo *target, QAngle &viewAngle, Vector &out);

    EntityInfo *GetClosestPlayer(QAngle &angle, QAngle &viewAngle);

    int GetWeaponID(uintptr_t entityPtr);

    void RCS(QAngle &angle, QAngle &viewAngle);

    void AddRC(QAngle &angle);

    void Smooth(QAngle &angle, QAngle &viewAngle, float val);

    void Enable();

    void Run();



    inline bool enabled = false;
    inline float bestFov = 6.0f;
    inline bool shouldRCS = false;
}


#endif //RASPTERNAL_AIMBOT_HPP
