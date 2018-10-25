#include "Keyboard.hpp"

// credits to ko1N

void Keyboard::Init() {
    this->fd = OpenKeyboardDevice(4); // HOMEWORK: Get this dynamically
}

int Keyboard::OpenKeyboardDevice(int dev) {
    char path[256];
    sprintf(path, "/dev/input/event%d", dev);

    return ::open(path, O_RDONLY | O_NONBLOCK);
}

void Keyboard::Run() {
    if (this->fd < 0) {
        return;
    }

    while (true) {
        struct input_event ev{};
        ssize_t n = ::read(this->fd, &ev, sizeof(ev));
        if (n == (ssize_t) -1 || n != sizeof(ev)) {
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