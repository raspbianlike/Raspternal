#include "Logger.hpp"

const char *modules[] = {"bhop", "glow", "triggerbot", "noflash"};

void Logger::Address(const char *str, uintptr_t address) {
    printf(ADDRESS_TITLE RESET BOLD "%s" CYAN " [" MAGENTA "%p" CYAN "]" RESET "\n", str, address);
}

void Logger::CLI() {
    printf(BOLD WHITE CYAN "[" RESET "Raspternal" BOLD CYAN "]$ " RESET);
}

void Logger::Modules() {
    //printf(BOLD WHITE CYAN "" BOLD WHITE CYAN "[" RESET BOLD RED "MODULE LIST" BOLD WHITE CYAN "]" RESET BOLD CYAN "\n" RESET);
    printf(BOLD WHITE CYAN "<?php " RESET BOLD RED "MODULELIST" RESET BOLD CYAN "\n" RESET);
    for (auto &it : modules)
        printf(BLUE BOLD "\t%s" RESET "\n", it);
    //printf(WHITE BOLD "- - - " RESET BLUE BOLD "%s" RESET "\n", it);

    printf(BOLD WHITE CYAN "?>" RESET" \n");
}

void Logger::Info(const char *str, ...) {
    char buffer[1024];
    va_list vlist;
    va_start(vlist, str);
    vsnprintf(buffer, 1024, str, vlist);
    va_end(vlist);
    printf(BOLD WHITE CYAN "[" RESET "INFO" BOLD CYAN "] " RESET CYAN "%s" CYAN RESET "\n", buffer);
}

void Logger::Debug(const char *str, ...) {
    char buffer[1024];
    va_list vlist;
    va_start(vlist, str);
    vsnprintf(buffer, 1024, str, vlist);
    va_end(vlist);
    printf(BOLD WHITE RED "[" RESET RED "DEBUG" BOLD RED "] " RESET CYAN "%s" CYAN RESET "\n", buffer);
}

void Logger::Error(const char *str) {
    printf(BOLD RED "[ERROR] " BOLD RED "%s" RESET "\n", str);
}

void Logger::Warning(const char *str) { // TODO: Fix
    printf(ADDRESS_TITLE RESET BOLD "%s" CYAN " [" MAGENTA "%p" CYAN "]" RESET "\n", str);
}