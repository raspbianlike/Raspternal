#ifndef RASPTERNAL_KEYCHECK_HPP
#define RASPTERNAL_KEYCHECK_HPP

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

inline Display *disp = XOpenDisplay(nullptr);

namespace KeyCheck {
    extern bool IsButtonDown(KeySym keySym);
}


#endif //RASPTERNAL_KEYCHECK_HPP