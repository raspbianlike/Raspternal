#ifndef RASPTERNAL_GLOW_HPP
#define RASPTERNAL_GLOW_HPP

#include "../Zero.hpp"
#include "../Hooker.hpp"
#include "../SDK/Entity.hpp"

#include "thread"
#include <pthread.h>

namespace Glow {
    template< class T >
    class CUtlVector {
    public:
        T* DataPtr; // 0000 (054612C0)
        unsigned int Max; // 0004 (054612C4)
        unsigned int unk02; // 0008 (054612C8)
        unsigned int Count; // 000C (054612CC)
        unsigned int DataPtrBack; // 0010 (054612D0)
    };

    struct GlowObjectDefinition_t {
        void* m_pEntity;
        float m_flGlowRed;
        float m_flGlowGreen;
        float m_flGlowBlue;
        float m_flGlowAlpha;
        uint8_t pad[16];
        bool m_bRenderWhenOccluded : 8;
        bool m_bRenderWhenUnoccluded : 8;
        bool m_bFullBloomRender : 8;
        unsigned char pad2;
        int m_nFullBloomStencilTestValue;
        int m_nSplitScreenSlot;
        int m_nNextFreeSlot;
        unsigned char pad3[4];

        static const int END_OF_FREE_LIST = -1;
        static const int ENTRY_IN_USE = -2;
    }; // sizeof() == 0x34

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

    void* Run(void*);

    void Start();

    inline pthread_t glow;
}


#endif //RASPTERNAL_GLOW_HPP
