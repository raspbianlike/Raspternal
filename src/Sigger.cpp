#include "Sigger.hpp"

void Sigger::Init() {
    csgo.Process("csgo_linux64");
    csgo.ProcessMaps();
    Logger::Info("Sig init Finished!");
}

void Sigger::FindLocalPlayer() {
    /*
        push    rbp
        cmp     edi, 0FFFFFFFFh
        mov     rax, cs:qword_1FD1610
        mov     rbp, rsp
        jz      short loc_7A2DCE
        lea     rax, qword_1FD1610
        movsxd  rdi, edi
        mov     rax, [rax+rdi*8]
     */

    uintptr_t getPlayerFunction = csgo.FindPattern("\x48\x89\xe5\x74\x0e\x48\x8d\x05", "xxxxxxxx", "client_panorama_client.so", "GetPlayerFunction");
    uintptr_t localPlayerMov = csgo.GetCallAddress(getPlayerFunction + 0x7);
    printf("pl %p\n", getPlayerFunction);
    printf("mov %p\n", localPlayerMov);
    csgo.ReadBuffer(localPlayerMov, &Offsets::LocalPlayer::instance, sizeof(uintptr_t));

    Logger::Address("Localplayer", Offsets::LocalPlayer::instance);
}

void Sigger::FindForceJumpAddress() {
    uintptr_t jumpMov = csgo.FindPattern("\x8B\x15\x00\x00\x00\x00\x89\xD8\x83\xC8\x02\xF6\xC2\x03\x0F\x45\xD8\x44\x89\xE0\xC1\xE0\x1E\xC1", "xx????xxxxxxxxxxxxxxxxxx",
                                         "client_panorama_client.so", "IN_JUMP Pointer");
    Offsets::Jump::IN_JUMP = csgo.GetCallAddress(jumpMov + 0x1);

    Logger::Address("IN_JUMP", Offsets::Jump::IN_JUMP);
}

void Sigger::FindGlowObjectManager() {
    uintptr_t glowManagerMov = csgo.FindPattern("\x48\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x48\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00",
                                                "xxx????????xx????xxxxxxx????????",
                                                "client_panorama_client.so", "Glow Manager");
    //Logger::Address("glowManagerStruct A", mov);
    //Logger::Address("glowManagerStruct -50", mov - 0x56);

    Offsets::GlowManager::memoryAddress = csgo.GetCallAddress(glowManagerMov - 0x55);

    Logger::Address("glowManagerStructA", Offsets::GlowManager::memoryAddress);
}

void Sigger::FindEntityList() {
    uintptr_t g_ppEntityListMov = csgo.FindPattern("\x48\x8B\x1D\x00\x00\x00\x00\x90\x48\x8B\x3B\x4C\x89\xF6\xE8\x00\x00\x00\x00\x48\x85\xC0\x49\x89\xC6",
                                                   "xxx????xxxxxxxx????xxxxxx", "client_panorama_client.so", "entitylist");

    /*
    push    r12
    xor     r12d, r12d
    push    rbx
    sub     rsp, 18h
    mov     r13, [rdi+410h]
    lea     rdi, aSearchingForCl ; "Searching for client entities with clas"...
    mov     rsi, r13
    call    _Msg
    mov     rbx, cs:off_18F79B0 <<-
    nop
    */
    uintptr_t g_ppEntityList = csgo.GetCallAddress(g_ppEntityListMov + 0x2);
    uintptr_t g_pEntityList;
    uintptr_t entityList;
    csgo.ReadBuffer(g_ppEntityList, &g_pEntityList, sizeof(uintptr_t));
    csgo.ReadBuffer(g_pEntityList, &entityList, sizeof(uintptr_t));

    Offsets::EntityList::entityListPointer = entityList;
    Logger::Address("entityList", Offsets::EntityList::entityListPointer);

}
