#include <chrono>
#include "Utils.hpp"

long Utils::GetEpochTime() {
    auto duration = std::chrono::system_clock::now().time_since_epoch();

    return std::chrono::duration_cast<std::chrono::milliseconds>( duration ).count();
}

CSWeaponType Utils::GetWeaponType(int weaponID) {
    switch (weaponID) {
        case WEAPON_DEAGLE:
        case WEAPON_ELITE:
        case WEAPON_FIVESEVEN:
        case WEAPON_GLOCK:
        case WEAPON_P250:
        case WEAPON_USP_SILENCER:
        case WEAPON_CZ75A:
        case WEAPON_REVOLVER:
        case WEAPON_TEC9:
        case WEAPON_HKP2000:
            return CSWeaponType::WEAPONTYPE_PISTOL;
        case WEAPON_AK47:
        case WEAPON_AUG:
        case WEAPON_FAMAS:
        case WEAPON_GALILAR:
        case WEAPON_M4A1:
        case WEAPON_SG556:
        case WEAPON_M4A1_SILENCER:
            return CSWeaponType::WEAPONTYPE_RIFLE;
        case WEAPON_SCAR20:
        case WEAPON_G3SG1:
        case WEAPON_AWP:
        case WEAPON_SSG08:
            return CSWeaponType::WEAPONTYPE_SNIPER_RIFLE;
        case WEAPON_M249:
        case WEAPON_NEGEV:
            return CSWeaponType::WEAPONTYPE_MACHINEGUN;
        case WEAPON_MAC10:
        case WEAPON_P90:
        case WEAPON_UMP45:
        case WEAPON_BIZON:
        case WEAPON_MP7:
        case WEAPON_MP9:
            return CSWeaponType::WEAPONTYPE_SUBMACHINEGUN;
        case WEAPON_XM1014:
        case WEAPON_MAG7:
        case WEAPON_SAWEDOFF:
        case WEAPON_NOVA:
            return CSWeaponType::WEAPONTYPE_SHOTGUN;
        case WEAPON_TASER:
        case WEAPON_KNIFE:
        case WEAPON_KNIFE_T:
        case WEAPON_KNIFE_BAYONET:
        case WEAPON_KNIFE_FLIP:
        case WEAPON_KNIFE_GUT:
        case WEAPON_KNIFE_KARAMBIT:
        case WEAPON_KNIFE_M9_BAYONET:
        case WEAPON_KNIFE_TACTICAL:
        case WEAPON_KNIFE_FALCHION:
        case WEAPON_KNIFE_SURVIVAL_BOWIE:
        case WEAPON_KNIFE_BUTTERFLY:
        case WEAPON_KNIFE_PUSH:
            return CSWeaponType::WEAPONTYPE_KNIFE;
        case WEAPON_FLASHBANG:
        case WEAPON_HEGRENADE:
        case WEAPON_SMOKEGRENADE:
        case WEAPON_MOLOTOV:
        case WEAPON_DECOY:
        case WEAPON_INCGRENADE:
            return CSWeaponType::WEAPONTYPE_GRENADE;
        case WEAPON_C4:
            return CSWeaponType::WEAPONTYPE_C4;
        default:
            return CSWeaponType::WEAPONTYPE_UNKNOWN;
    }
}
