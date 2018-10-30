#ifndef RASPTERNAL_KEYCHECK_HPP
#define RASPTERNAL_KEYCHECK_HPP

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

#include <fstream>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <zconf.h>
#include <linux/input.h>
#include <thread>

inline Display *disp = nullptr;

class Keyboard {
public:
    void Init();

    int OpenKeyboardDevice();

    int* FindKeyboardDevice(int dev);

    void Run();

    bool IsButtonDown(int key);

private:
    int fd = -1;
    bool keystate[256];
};

inline Keyboard keyboard;

#endif //RASPTERNAL_KEYCHECK_HPP
