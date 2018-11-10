#include "Input.hpp"

// credits to ko1N

void Input::Init(DeviceTypes type) {
    this->type = type;
    OpenDevice();
    Logger::Info("Waiting for device...");

    while (this->fd == -1);
    Logger::Info("Found Device, ID: %i\n", this->fd);
}

void Input::FindDevice(int dev) {
    char path[256];
    sprintf(path, "/dev/input/event%d", dev);
    int fd = open(path, O_RDONLY | O_NONBLOCK);
    while (this->fd == -1) {
        while (true) {
            struct input_event ev;
            ssize_t n = ::read(fd, &ev, sizeof(ev));
            if (n != sizeof(ev)) {
                break;
            }
            if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) // got keyboard event, assign fd
                this->fd = fd;
        }
    }
}

void Input::OpenDevice() {
    if (type == ms) {
        char path[256];
        sprintf(path, "/dev/input/mouse0");
        fd = open(path, O_RDONLY | O_NONBLOCK);
    } else {
        for (int i = 0; i < 127; i++)
            std::thread(&Input::FindDevice, this, i).detach();
    }
}

void Input::Run() {
    if (this->fd < 0) {
        return;
    }

    while (true) {
        struct input_event ev;
        unsigned char data[3];
        ssize_t n;
        if (type == kb)
            n = ::read(this->fd, &ev, sizeof(ev));
        else
            n = ::read(this->fd, data, 3);
        ssize_t s = (type == kb) ? sizeof(ev) : 3;
        if (n == -1 || n != s) {
            break;
        }

        if (ev.type == EV_KEY && type == kb && ev.value >= 0 && ev.value <= 2) {
            this->keystate[ev.code] = ev.value > 0;
        } else if (type == ms) {
            memcpy(buttonState, data, 3);
        }
    }
}

bool Input::IsButtonDown(int key) {
    this->Run();
    if ((key < 0 || key >= 256) && type == kb)
        return false;

    if (type == ms) {
        return (buttonState[0] & key);
    }

    return this->keystate[key];
}