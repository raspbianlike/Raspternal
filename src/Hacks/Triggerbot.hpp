#ifndef RASPTERNAL_TRIGGERBOT_HPP
#define RASPTERNAL_TRIGGERBOT_HPP

#include "../SDK/SDK.hpp"
#include "../SDK/Entity.hpp"
#include "../SDK/CBasePlayer.hpp"
#include "../SDK/KeyCheck.hpp"


namespace Triggerbot {
    void Start();

    void Stop();

    void *Run(void *);

    inline pthread_t triggerbot;

    inline bool enabled = false;

    inline int crosshairIndex = 0;
};


#endif //RASPTERNAL_TRIGGERBOT_HPP
