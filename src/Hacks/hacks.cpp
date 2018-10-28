#include "hacks.hpp"


void Hacks::Run() {
    try {
        Misc::BHop::Run();
        Misc::NoFlash::Run();
        Triggerbot::Run();
        Glow::Run();
    }
    catch(std::exception& e) {
        Logger::Error(e.what());
    }
}