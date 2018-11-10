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
    void Run();

    void Smooth(Vector &angle, Vector &viewAngle, float val);

    EntityInfo *GetClosestPlayer(Vector &angle, Vector &viewAngle);

    void GetClosestBone(Vector &viewAngle, Vector& out, EntityInfo* target);

    void RCS(Vector &angle, Vector &viewAngle);

    void AddRC(Vector &angle);

    void Enable();

    int GetWeaponID(uintptr_t entityPtr);

    inline bool enabled = false;

    inline float bestFov = 6.0f;

    inline bool shouldRCS = false;
}


#endif //RASPTERNAL_AIMBOT_HPP
