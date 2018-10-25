#ifndef RASPTERNAL_TRIGGERBOT_HPP
#define RASPTERNAL_TRIGGERBOT_HPP

#include "../SDK/SDK.hpp"
#include "../SDK/Entity.hpp"
#include "../SDK/CBaseEntity.hpp"
#include "../SDK/Keyboard.hpp"

extern "C" {
#include <xdo.h>
}

namespace Triggerbot {
    void Start();

    void Stop();

    void *Run(void *);

    inline pthread_t triggerbot;

    inline bool enabled = false;

    inline int crosshairIndex = 0;

    inline xdo_t *xdo = xdo_new(nullptr);
};


#endif //RASPTERNAL_TRIGGERBOT_HPP
