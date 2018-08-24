#include "KeyCheck.hpp"

bool KeyCheck::IsButtonDown(KeySym keySym) {

    char szKey[32];
    int iKeyCodeToFind = XKeysymToKeycode(disp, keySym);

    XQueryKeymap(disp, szKey);

    return szKey[iKeyCodeToFind / 8] & (1 << (iKeyCodeToFind % 8));
}