#ifndef RASPTERNAL_MISC_HPP
#define RASPTERNAL_MISC_HPP

#include "../Sigger.hpp"
#include "../SDK/definitions.hpp"
#include "../SDK/Input.hpp"
#include "../SDK/EntityList.hpp"

namespace Misc {
    namespace NoFlash {
        void Enable();

        void Run();

        inline bool enabled;
    }

    namespace BHop {
        void Enable();

        void Run();

        inline bool enabled;
    }
}


#endif //RASPTERNAL_MISC_HPP
