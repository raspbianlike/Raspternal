#ifndef RASPTERNAL_CGLOBALVARS_HPP
#define RASPTERNAL_CGLOBALVARS_HPP

struct CGlobalVars {
public:
    float realtime;
    int framecount;
    float absoluteframetime;
    float absoluteframestarttimestddev;
    float curtime;
    float frametime;
    int maxClients;
    int tickcount;
    float interval_per_tick;
    float interpolation_amount;
    int simTicksThisFrame;
    int network_protocol;
    void* pSaveData;
    bool m_bClient;
    bool m_bRemoteClient;
};

#endif  // RASPTERNAL_CGLOBALVARS_HPP
