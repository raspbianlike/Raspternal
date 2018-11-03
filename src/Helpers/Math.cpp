#include "Math.hpp"

Vector Math::CalcAngle(Vector &src, Vector &dst) {
    Vector ret;
    Vector delta((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));
    double hyp = sqrtf(delta.x * delta.x + delta.y * delta.y);

    ret.x = asinf(delta.z / hyp) * 180.0f / M_PI;
    ret.y = atanf(delta.y / delta.x) * 180.0f / M_PI;
    ret.z = 0.0f;

    if (delta.x >= 0.0)
        ret.y += 180.0f;

    return ret;
}

void Math::Clamp(Vector &vec) {
    while (vec.y > 180)
        vec.y -= 360;
    while (vec.y < -180)
        vec.y += 360;

    if (vec.x > 89)
        vec.x = 89;
    else if (vec.x < -89)
        vec.x = -89;

    if (vec.y != vec.y)
        vec.y = 0;

    if (vec.x != vec.x)
        vec.x = 0;

}

float Math::AngleFOV(const Vector &viewAngle, const Vector &aimAngle) {
    Vector delta = viewAngle - aimAngle;
    delta.Normalize();
    float fov = sqrtf(delta.x * delta.x + delta.y * delta.y);
    if (fov > 180.0f)
        fov -= 360.0f;
    fov = fabsf(fov);
    return fov;
}