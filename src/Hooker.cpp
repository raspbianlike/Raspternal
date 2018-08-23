#include "Hooker.hpp"

void Hooker::Init() {
    csgo.Process("csgo_linux64");
    csgo.ProcessMaps();
    Logger::Info("Hooker init Finished!");
}

void Hooker::FindLocalPlayer() {
    uintptr_t getPlayerFunction = csgo.FindPattern("\x48\x89\xe5\x74\x0e\x48\x8d\x05", "xxxxxxxx", "client_panorama_client.so", "GetPlayerFunction");
    uintptr_t localPlayerMov = csgo.GetCallAddress(getPlayerFunction + 0x7);
    csgo.ReadBuffer(localPlayerMov, &Offsets::LocalPlayer::instance, sizeof(uintptr_t));

    Logger::Address("Localplayer", Offsets::LocalPlayer::instance);
}

void Hooker::FindForceJumpAddress() {
    uintptr_t jumpMov = csgo.FindPattern("\x8B\x15\x00\x00\x00\x00\x89\xD8\x83\xC8\x02\xF6\xC2\x03\x0F\x45\xD8\x44\x89\xE0\xC1\xE0\x1E\xC1", "xx????xxxxxxxxxxxxxxxxxx", "client_panorama_client.so", "IN_JUMP Pointer");
    Offsets::Jump::IN_JUMP = csgo.GetCallAddress(jumpMov + 0x1);

    Logger::Address("IN_JUMP", Offsets::Jump::IN_JUMP);
}

void Hooker::FindGlowObjectManager() {
    uintptr_t glowManagerMov = csgo.FindPattern("\x48\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x48\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00", "xxx????????xx????xxxxxxx????????",
                                                "client_panorama_client.so", "Glow Manager");
    //Logger::Address("glowManagerStruct A", mov);
    //Logger::Address("glowManagerStruct -50", mov - 0x56);

    Offsets::GlowManager::memoryAddress = csgo.GetCallAddress(glowManagerMov - 0x55);

    Logger::Address("glowManagerStructA", Offsets::GlowManager::memoryAddress);
}