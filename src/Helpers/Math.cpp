#include "Math.hpp"

Vector Math::CalcAngle(Vector *source, Vector *target) {
    Vector angle;
    Vector delta = {
            (source->x - target->x), (source->y - target->y), (source->z - target->z)};
    //cout<<"delta x y z "<<delta.x<<", "<<delta.y<<", "<<delta.z<<endl;
    double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
    angle.x = (float) (atanf(delta.z / hyp) * 180.0f / M_PI);
    angle.y = (float) (atanf(delta.y / delta.x) * 180.0f / M_PI);
    angle.z = 0.0f;
    //cout<<"angle x y z "<<angle.x<<", "<<angle.y<<", "<<angle.z<<endl;
    if (delta.x >= 0) {
        angle.y += 180;
    }
    return angle;
}

void Math::Clamp(Vector &vec) {
    while (vec.y > 180) {
        vec.y -= 360;
    }
    while (vec.y < -180) {
        vec.y += 360;
    }
    if (vec.x > 89) {
        vec.x = 89;
    } else if (vec.x < -89) {
        vec.x = -89;
    }
    if (vec.y != vec.y) {
        //cout<<"problem y "<<endl;
        vec.y = 0;
    }
    if (vec.x != vec.x) {
        //cout<<"problem x "<<endl;
        vec.x = 0;
    }
}

float Math::AngleFOV(const Vector &viewAngle, const Vector &aimAngle) {
    Vector delta = aimAngle - viewAngle;
    delta.Normalize();

    return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}