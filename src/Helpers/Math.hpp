#ifndef RASPTERNAL_MATH_HPP
#define RASPTERNAL_MATH_HPP

#include "../SDK/Vector.hpp"
#include "../SDK/QAngle.hpp"

namespace Math {
    QAngle CalcAngle(Vector &source, Vector &target);

    void Clamp(QAngle &angles);

    float AngleFOV(const QAngle &viewAngle, const QAngle &aimAngle);
}
#endif  // RASPTERNAL_MATH_HPP
