#include "Math.hpp"

/* Calculates X/Y Angle diff from Point A to Point B */
QAngle Math::CalcAngle(Vector &src, Vector &dst) {
    QAngle ret;
    Vector delta = src - dst;
    double hyp = delta.Length2D();

    ret[PITCH] = (asinf(delta.z / hyp)) * 180.0f / M_PI;
    ret[YAW] = (atanf(delta.y / delta.x)) * 180.0f / M_PI;

    //if (delta.x >= 0.0f)
      //  ret[YAW] += 180.0f;

    return ret;
}

void Math::Clamp(QAngle &angles) {
    if( angles[YAW] > 180.0f ){
        angles[YAW] = 180.0f;
    } else if( angles[YAW] < -180.0f ){
        angles[YAW] = -180.0f;
    }

    if( angles[PITCH] > 89.0f ){
        angles[PITCH] = 89.0f;
    } else if( angles[PITCH] < -89.0f ){
        angles[PITCH] = -89.0f;
    }
    angles[ROLL] = 0.0f;
}

float Math::AngleFOV(const QAngle &viewAngle, const QAngle &aimAngle) {
    QAngle delta = viewAngle - aimAngle;
    delta.Normalize();
    float fov = sqrtf(delta.x * delta.x + delta.y * delta.y);
    if (fov > 180.0f)
        fov -= 360.0f;

    fov = fabsf(fov);

    return fov;
}