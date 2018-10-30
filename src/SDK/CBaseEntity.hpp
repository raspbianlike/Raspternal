#ifndef RASPTERNAL_CBASENTITY_HPP
#define RASPTERNAL_CBASENTITY_HPP

#include "Entity.hpp"
#include "SDK.hpp"

extern Entity localPlayer;
extern std::array<Entity, 64> entities;

namespace CBaseEntity {
    extern Entity GetEntity(int index);
}


#endif //RASPTERNAL_C_BASENTITY_HPP
