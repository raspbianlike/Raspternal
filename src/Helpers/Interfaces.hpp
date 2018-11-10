#ifndef RASPTERNAL_INTERFACES_HPP
#define RASPTERNAL_INTERFACES_HPP

#include "../SDK/SDK.hpp"
#include <cstdint>

struct InterfaceReg {
};


namespace Interfaces {
    uintptr_t GetInferface(const char *lib, const char *version);
};


#endif //RASPTERNAL_INTERFACES_HPP
