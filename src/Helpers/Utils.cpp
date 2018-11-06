#include <chrono>
#include "Utils.hpp"

long Utils::GetEpochTime() {
    auto duration = std::chrono::system_clock::now().time_since_epoch();

    return std::chrono::duration_cast<std::chrono::milliseconds>( duration ).count();
}
