#ifndef RASPTERNAL_TRIGGERBOT_HPP
#define RASPTERNAL_TRIGGERBOT_HPP

#include "../SDK/SDK.hpp"
#include "../SDK/definitions.hpp"
#include "../SDK/EntityList.hpp"
#include "../SDK/Input.hpp"

extern "C" {
#include <xdo.h>
}

namespace Triggerbot {
    void Enable();

    void Run();

    inline bool enabled = false;

    inline int crosshairIndex = 0;

    inline xdo_t *xdo = xdo_new(nullptr);
};


#endif //RASPTERNAL_TRIGGERBOT_HPP
