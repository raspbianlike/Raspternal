#include "Zero.hpp"
#include "Logger.hpp"
#include "Hooker.hpp"

#include "Hacks/hacks.hpp"

#include <iostream>
#include <link.h>
#include <thread>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>

using namespace std;

void Init() {
    Hooker::Init();
    Hooker::FindLocalPlayer();
    Hooker::FindForceJumpAddress();
    Hooker::FindGlowObjectManager();

    Logger::Info("Init finished!");
}

int main() {
    Init();

    Glow::Start();
    BHop::Start();

    // The below will be implemented as some sort of cli console to manage modules
    // Soon:tm:
    // getchar();
    // pthread_cancel(Glow::glow);

    for(;;)
        ;
}