#ifndef RASPTERNAL_HOOKER_HPP
#define RASPTERNAL_HOOKER_HPP

#include "Zero.hpp"
#include "Helpers/Helpers.hpp"

inline Zero csgo;

struct sOffsets {
    struct sLocalPlayer {
        uintptr_t instance;
        uintptr_t health = 0x134;
        uintptr_t flags = 0x138;
        uintptr_t flash = 0xAC10;
        uintptr_t shoot = 0xABB0;
        uintptr_t crosshairID = 0xBC08;
        uintptr_t aimPunch = 0x3764;
    } localPlayer;

    struct sJump {
        uintptr_t IN_JUMP;
    } forceJump;

    struct sGlowManager {
        uintptr_t memoryAddress;
    } glowManager;

    struct sEntityList {
        uintptr_t entityListPointer;
    } entityList;

    struct sGlobalVars {
        uintptr_t globalVars;
    } globalVars;

    struct sEntity {
        uintptr_t studioBones = 0x2C70;
        uintptr_t viewMatrix = 0x2537374;
    } entity;

    struct sInterface {
        uintptr_t interfaceReg;
    } interface;

    struct sEngine {
        uintptr_t base;
        uintptr_t viewAngles = 0x8E28;
        uintptr_t signOnState = 0x1A8;
        uintptr_t localPlayerIndex = 0x21C;
        uintptr_t mapName = 0x228;
    } engine;

    struct sWeapon {
        uintptr_t m_AttributeManager = 0x34c0;
        uintptr_t m_hActiveWeapon = 0x3628;
        uintptr_t m_iItemDefinitionIndex = 0x268;
        //uintptr_t m_AttributeManager = 0x34c0;
    }weapon;

} inline Offsets;


class Sigger {
public:
    static void Init();

    static void FindLocalPlayer();

    static void FindForceJumpAddress();

    static void FindGlowObjectManager();

    static void FindEntityList();

    static void FindGlobalVars();

    static void FindInterfaceRegs();

    static void FindEngineFunctions();
};

inline Sigger sigger;

#endif //RASPTERNAL_HOOKER_HPP
