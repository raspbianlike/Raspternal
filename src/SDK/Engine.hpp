#ifndef RASPTERNAL_ENGINE_HPP
#define RASPTERNAL_ENGINE_HPP


#include "QAngle.hpp"
#include "SDK.hpp"


class Engine {
public:
    void GetViewAngles(QAngle &out) {
        if (!IsInGame())
            return;
        csgo.ReadBuffer(Offsets.engine.base + Offsets.engine.viewAngles, &out, sizeof(QAngle));
    }

    void SetViewAngles(QAngle &in) {
        csgo.WriteBuffer(Offsets.engine.base + Offsets.engine.viewAngles, &in, sizeof(QAngle));
    }

    bool IsInGame() {
        int sign;
        csgo.ReadBuffer(Offsets.engine.base + Offsets.engine.signOnState, &sign, sizeof(int));
        return sign == 6;
    }

    int GetLocalPlayer() {
        int index;
        csgo.ReadBuffer(Offsets.engine.base + Offsets.engine.localPlayerIndex, &index, sizeof(int));
        return index;
    }

    void GetMapName(char *buf) {
        if (!IsInGame())
            buf = nullptr;

        csgo.ReadBuffer(Offsets.engine.base + Offsets.engine.mapName, buf, 40);
    }
};

inline Engine engine;
#endif  // RASPTERNAL_ENGINE_HPP
