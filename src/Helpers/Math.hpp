#ifndef RASPTERNAL_MATH_HPP
#define RASPTERNAL_MATH_HPP

#include "../SDK/Vector.hpp"

namespace Math {
    Vector CalcAngle(Vector &source, Vector &target);

    void Clamp(Vector &vec);

    float AngleFOV(const Vector &viewAngle, const Vector &aimAngle);
}
#endif  // RASPTERNAL_MATH_HPP
