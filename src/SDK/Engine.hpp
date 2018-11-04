#ifndef RASPTERNAL_ENGINE_HPP
#define RASPTERNAL_ENGINE_HPP


#include "Vector.hpp"
#include "SDK.hpp"

using namespace Offsets::Engine;

class Engine {
public:
    void GetViewAngles(Vector &out) {
        if (!IsInGame())
            return;
        csgo.ReadBuffer(viewAngles + base, &out, sizeof(Vector));
    }

    void SetViewAngles(Vector &in) {
        if (!IsInGame())
            return;
        csgo.WriteBuffer(viewAngles + base, &in, sizeof(Vector));
    }

    bool IsInGame() {
        int sign;
        csgo.ReadBuffer(base + signOnState, &sign, sizeof(int));
        return sign == 6;
    }

    const char *GetMapName(char *buf) {
        if (!IsInGame())
            return nullptr;
        csgo.ReadBuffer(mapName + base, buf, 40);
    }
};

inline Engine engine;
#endif  // RASPTERNAL_ENGINE_HPP
