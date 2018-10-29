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
    }

    namespace Jump {
        inline uintptr_t IN_JUMP;
    }

    namespace GlowManager {
        inline uintptr_t memoryAddress;
    }

    namespace EntityList {
        inline uintptr_t entityListPointer = NULL;
    }
}


class Hooker {
public:
    static void Init();

    static void FindLocalPlayer();

    static void FindForceJumpAddress();

    static void FindGlowObjectManager();

    static void FindEntityList();
};


#endif //RASPTERNAL_HOOKER_HPP
