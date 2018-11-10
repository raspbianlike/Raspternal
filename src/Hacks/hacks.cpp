#include "hacks.hpp"


void Hacks::Run() {
    try {
        Misc::BHop::Run();
        Misc::NoFlash::Run();
        Aimbot::Run();
        Triggerbot::Run();
        Glow::Run();
    }
    catch (std::exception &e) {
        Logger::Error(e.what());
    }
}