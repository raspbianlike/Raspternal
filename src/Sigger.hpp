#ifndef RASPTERNAL_HOOKER_HPP
#define RASPTERNAL_HOOKER_HPP

#include "Zero.hpp"
#include "Helpers/Helpers.hpp"

inline Zero csgo;

namespace Offsets {
    namespace LocalPlayer {
        inline uintptr_t instance;
        inline uintptr_t health = 0x134;
        inline uintptr_t flags = 0x138;
        inline uintptr_t flash = 0xAC10;
        inline uintptr_t shoot = 0xABB0;
        inline uintptr_t crosshairID = 0xBC08;
        inline uintptr_t aimPunch = 0x3764;
    }

    namespace Jump {
        inline uintptr_t IN_JUMP;
    }

    namespace GlowManager {
        inline uintptr_t memoryAddress;
    }

    namespace EntityList {
        inline uintptr_t entityListPointer;
    }

    namespace GlobalVars {
        inline uintptr_t globalVars;
    }

    namespace Entity {
        inline uintptr_t studioBones = 0x2C70;
        inline uintptr_t viewMatrix = 0x2537374;
    }

    namespace Interface {
        inline uintptr_t interfaceReg;
    }

    namespace ClientState {
        inline uintptr_t viewAngles;
    }
}


class Sigger {
public:
    static void Init();

    static void FindLocalPlayer();

    static void FindForceJumpAddress();

    static void FindGlowObjectManager();

    static void FindEntityList();

    static void FindGlobalVars();

    static void FindInterfaceRegs();

    static void FindViewAngle();
};


#endif //RASPTERNAL_HOOKER_HPP
