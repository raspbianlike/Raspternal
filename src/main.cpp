#include "Zero.hpp"
#include "Logger.hpp"
#include "Hooker.hpp"

#include <iostream>
#include <link.h>
#include <thread>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>

using namespace std;

Display *disp = XOpenDisplay(0);
KeyCode modcode = 0; //init value

bool GetKeyState(KeySym keySym) {

    char szKey[32];
    int iKeyCodeToFind = XKeysymToKeycode(disp, keySym);

    XQueryKeymap(disp, szKey);

    return szKey[iKeyCodeToFind / 8] & (1 << (iKeyCodeToFind % 8));
}

void Init() {
    Hooker::Init();
    Hooker::FindLocalPlayer();
    Hooker::FindForceJumpAddress();
    Hooker::FindGlowObjectManager();

    Logger::Info("Init finished!");
}

int main() {
    Init();
    return 0;
}