#ifndef RASPTERNAL_ENGINE_HPP
#define RASPTERNAL_ENGINE_HPP


#include "Vector.hpp"
#include "SDK.hpp"


class Engine {
public:
    void GetViewAngles(Vector &out) {
        if (!IsInGame())
            return;
        csgo.ReadBuffer(Offsets.engine.base + Offsets.engine.viewAngles, &out, sizeof(Vector));
    }

    void SetViewAngles(Vector &in) {
        csgo.WriteBuffer(Offsets.engine.base + Offsets.engine.viewAngles, &in, sizeof(Vector));
    }

    bool IsInGame() {
        int sign;
        csgo.ReadBuffer(Offsets.engine.base + Offsets.engine.signOnState, &sign, sizeof(int));
        return sign == 6;
    }

    void GetMapName(char *buf) {
        if (!IsInGame())
            buf = nullptr;

        csgo.ReadBuffer(Offsets.engine.base + Offsets.engine.mapName, buf, 40);
    }
};

inline Engine engine;
#endif  // RASPTERNAL_ENGINE_HPP
