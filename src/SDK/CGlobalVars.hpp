#ifndef RASPTERNAL_CGLOBALVARS_HPP
#define RASPTERNAL_CGLOBALVARS_HPP

struct CGlobalVars {
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
};

extern CGlobalVars globalVars;

#endif  // RASPTERNAL_CGLOBALVARS_HPP
