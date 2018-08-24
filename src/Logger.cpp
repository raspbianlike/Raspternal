#include "Logger.hpp"


void Logger::Address(const char *str, uintptr_t address) {
    printf(ADDRESS_TITLE RESET BOLD "%s" CYAN " [" MAGENTA "%p" CYAN "]" RESET "\n", str, address);
}
void Logger::CLI() {
    printf(BOLD WHITE CYAN "[" RESET "Raspternal" BOLD CYAN "]$ " RESET);
}

void Logger::Info(const char *str) { // TODO: Make less gay
    printf(BOLD WHITE CYAN "[" RESET "LOG" BOLD CYAN "] " RESET CYAN "%s" CYAN RESET "\n", str);
}

void Logger::Error(const char *str) {
    printf(BOLD RED "[ERROR] " BOLD RED "%s" RESET "\n", str);
}

void Logger::Warning(const char *str) { // TODO: Fix
    printf(ADDRESS_TITLE RESET BOLD "%s" CYAN " [" MAGENTA "%p" CYAN "]" RESET "\n", str);
}