#ifndef RASPTERNAL_GLOW_HPP
#define RASPTERNAL_GLOW_HPP

#include "../SDK/definitions.hpp"
#include "../SDK/SDK.hpp"
#include "../SDK/EntityList.hpp"
#include "Triggerbot.hpp"
#include "../settings.hpp"

namespace Glow {
    template<class T>
    class CUtlVector {
    public:
        T *DataPtr; // 0000 (054612C0)
        unsigned int Max; // 0004 (054612C4)
        unsigned int unk02; // 0008 (054612C8)
        unsigned int Count; // 000C (054612CC)
        unsigned int DataPtrBack; // 0010 (054612D0)
    };

    struct GlowObjectDefinition_t {
        void *m_pEntity; // 0x0
        float r; // 0x8
        float g; // 0xC
        float b; // 0x10
        float a; // 0x14
        uint8_t pad[0x10]; // 0x18
        bool m_bRenderWhenOccluded : 8; // 0x28
        bool m_bRenderWhenUnoccluded : 8; // 0x29
        bool m_bFullBloomRender : 8; // 0x2A
        unsigned char pad2; // 0x2B
        int m_nFullBloomStencilTestValue; // 0x2C
        int m_nSplitScreenSlot; // 0x30
        int m_nNextFreeSlot; // 0x34
        unsigned char pad3[0x4]; // 0x38

        static const int END_OF_FREE_LIST = -1;
        static const int ENTRY_IN_USE = -2;
    }; // sizeof() == 0x40

    class CGlowObjectManager {
    public:
        CUtlVector<GlowObjectDefinition_t> m_GlowObjectDefinitions; // 0000
        int m_nFirstFreeSlot; // 0014 (054612D4)
        unsigned int unk1; // 0018 (054612D8)
        unsigned int unk2; // 001C (054612DC)
        unsigned int unk3; // 0020 (054612E0)
        unsigned int unk4; // 0024 (054612E4)
        unsigned int unk5; // 0028 (054612E8)
    };

    void Run();

    void Enable();

    inline bool enabled = false;
}


#endif //RASPTERNAL_GLOW_HPP
