#ifndef RASPTERNAL_CGLOBALVARS_HPP
#define RASPTERNAL_CGLOBALVARS_HPP

#include "SDK.hpp"

class CGlobalVars {
public:
    float realtime; // 0x0
    int framecount; // 0x4
    float absoluteframetime; // 0x8
    float absoluteframestarttimestddev; // 0xC
    float curtime; // 0x10
    float frametime; // 0x14
    int maxClients; // 0x18
    int tickcount; // 0x1C
    float interval_per_tick; // 0x20
    float interpolation_amount;
    int simTicksThisFrame;
    int network_protocol;
    void *pSaveData;
    bool m_bClient;
    bool m_bRemoteClient;

    CGlobalVars GetGlobalVars() {
        CGlobalVars tmp{};
        csgo.ReadBuffer(Offsets::GlobalVars::globalVars, &tmp, sizeof(CGlobalVars));
        return tmp;
    };

    void UpdateGlobalVars() {
        csgo.ReadBuffer(Offsets::GlobalVars::globalVars, this, sizeof(CGlobalVars));
    };
};

extern CGlobalVars globalVars;

#endif  // RASPTERNAL_CGLOBALVARS_HPP
