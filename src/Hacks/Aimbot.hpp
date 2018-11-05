#ifndef RASPTERNAL_AIMBOT_HPP
#define RASPTERNAL_AIMBOT_HPP

#include "../Helpers/Logger.hpp"
#include "../SDK/Vector.hpp"


namespace Aimbot {
    void Run();

    void Smooth(Vector& angle, Vector& viewAngle, float val);

    void RCS(Vector& angle, Vector& viewAngle);

    void Enable();

    inline bool enabled = false;
}


#endif //RASPTERNAL_AIMBOT_HPP
