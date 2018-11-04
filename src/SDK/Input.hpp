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

enum DeviceTypes {
    ms,
    kb
};
class Input {
public:
    void Init(DeviceTypes type);

    void OpenDevice();

    void FindDevice(int dev);

    void Run();

    bool IsButtonDown(int key);

private:
    int fd = -1;
    bool keystate[257];
    unsigned char buttonState[3];
    DeviceTypes type;
};

inline Input keyboard;
inline Input mouse;

#endif //RASPTERNAL_KEYCHECK_HPP
