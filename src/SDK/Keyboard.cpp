#include "Keyboard.hpp"
#include "../Helpers/Logger.hpp"

// credits to ko1N

void Keyboard::Init() {
    OpenKeyboardDevice();
    Logger::Info("Waiting for Keyboard...");

    while(this->fd == -1);
    Logger::Info("Found Keyboard, ID: %i\n", this->fd);
}

int *Keyboard::FindKeyboardDevice(int dev) {
    char path[256];
    sprintf(path, "/dev/input/event%d", dev);
    int fd = open(path, O_RDONLY | O_NONBLOCK);
    while(this->fd == -1) {
        while (true) {
            struct input_event ev;
            ssize_t n = ::read(fd, &ev, sizeof(ev));
            if (n != sizeof(ev))
                break;
            if (ev.type == EV_KEY) // got keyboard event, assign fd
                this->fd = fd;
        }
    }
}

int Keyboard::OpenKeyboardDevice() {
    for (int i = 0; i < 127; i++)
        std::thread(&Keyboard::FindKeyboardDevice, this, i).detach();
}

void Keyboard::Run() {
    if (this->fd < 0) {
        return;
    }

    while (true) {
        struct input_event ev;
        ssize_t n = ::read(this->fd, &ev, sizeof(ev));
        if (n != sizeof(ev)) {
            break;
        }

        // check if it was a keyboard event
        if (ev.type == EV_KEY &&
            ev.value >= 0 && ev.value <= 2) {
            this->keystate[ev.code] = ev.value > 0;
        }
    }
}

bool Keyboard::IsButtonDown(int key) {
    this->Run();
    if (key < 0 || key >= 256)
        return false;
    return this->keystate[key];
}