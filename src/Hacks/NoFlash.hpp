#ifndef RASPTERNAL_MISC_HPP
#define RASPTERNAL_MISC_HPP

#include "../Hooker.hpp"
#include "../SDK/SDK.hpp"

namespace NoFlash {
    // TODO: Implement

    void Start();

    void Stop();

    void *Run(void *);

    inline pthread_t noflash;

    inline bool enabled = false;
}


#endif //RASPTERNAL_MISC_HPP
