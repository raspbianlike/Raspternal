#ifndef RASPTERNAL_BHOP_HPP
#define RASPTERNAL_BHOP_HPP

#include "../SDK/SDK.hpp"
#include "../SDK/Entity.hpp"
#include "../SDK/KeyCheck.hpp"

namespace BHop {
    void Start();

    void *Run(void *);

    inline pthread_t bhop;
}

#endif //RASPTERNAL_BHOP_HPP
