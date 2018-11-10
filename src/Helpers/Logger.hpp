#ifndef RASPTERNAL_LOGGER_HPP
#define RASPTERNAL_LOGGER_HPP

#define ADDRESS_TITLE BOLD CYAN "[" MAGENTA  "ADDRESS" CYAN "] " RESET

#define RESET        "\x1B[0m"
#define RED        "\x1B[31m"
#define GREEN        "\x1B[32m"
#define YELLOW        "\x1B[33m"
#define BLUE        "\x1B[34m"
#define MAGENTA        "\x1B[35m"
#define CYAN        "\x1B[36m"
#define WHITE        "\x1B[37m"
#define BOLD        "\x1B[1m"
#define UNDERLINE    "\x1B[4m"

#include "../Zero.hpp"
#include <stdarg.h>


class Logger {
public:
    static void Address(const char *str, uintptr_t address);

    static void CLI();

    static void Info(const char *str, ...);

    static void Debug(const char *str, ...);

    static void Modules();

    static void Error(const char *str);

    static void Warning(const char *str);
};


#endif //RASPTERNAL_LOGGER_HPP
