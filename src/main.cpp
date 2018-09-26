#include "Zero.hpp"

#include "Hacks/hacks.hpp"
#include <cstddef>

using namespace std;

template<typename Out>
void split(const std::string &s, char delim, Out result) { // this is pasted thanks to stackoverflow
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

enum cmds {
    help,
    module,
};
enum operations {
    enable,
    disable
};
enum modules {
    all,
    list,
    glow,
    bhop,
    triggerbot,
    noflash
};

void ProcessCommand(string message) {
    vector<string> parts;
    parts = split(message, ' ');

    cmds cmd;
    modules mod;
    operations operation;
    // check first parts
    if (parts[0] == "help") {
        cmd = help;
    } else if (parts[0] == "module")
        cmd = module;

    switch (cmd) {
        case help:
            // do nothing, just output a help menu
            //Logger::Help(); // TODO: Implement this
            break;
        case module:
            // check for module name and perform operation on it
            if (parts.size() < 2) {
                Logger::Error("Unknown command!");
                return;
            }

            if (parts[1] == "list")
                mod = list;
            if (parts[1] == "glow")
                mod = glow;
            else if (parts[1] == "bhop")
                mod = bhop;
            else if (parts[1] == "triggerbot")
                mod = triggerbot;
            else if (parts[1] == "noflash")
                mod = noflash;
            else if (parts[1] == "all")
                mod = all;

            if (mod != list) {
                if (parts[2] == "enable")
                    operation = enable;
                else if (parts[2] == "disable")
                    operation = disable;
            }

            switch (mod) {
                case all:
                    if (operation == enable) {
                        BHop::Start();
                        Glow::Start();
                        Triggerbot::Start();
                        NoFlash::Start();
                    } else if (operation == disable) {
                        BHop::Stop();
                        Glow::Stop();
                        Triggerbot::Stop();
                        NoFlash::Stop();
                    }
                    break;
                case list:
                    Logger::Modules();
                    break;
                case bhop:
                    if (operation == enable)
                        BHop::Start();
                    else if (operation == disable)
                        BHop::Stop();
                    break;
                case glow:
                    if (operation == enable)
                        Glow::Start();
                    else if (operation == disable)
                        Glow::Stop();
                    break;
                case triggerbot:
                    if (operation == enable)
                        Triggerbot::Start();
                    else if (operation == disable)
                        Triggerbot::Stop();
                    break;
                case noflash:
                    if (operation == enable)
                        NoFlash::Start();
                    else if (operation == disable)
                        NoFlash::Stop();
                    break;
                default:
                    Logger::Error("Unknown command!");
            }
            break;
        default:
            Logger::Error("Unknown command!");
    }
}

void Init() {
    KeyCheck::Init();
    Hooker::Init();
    Hooker::FindLocalPlayer();
    Hooker::FindForceJumpAddress();
    Hooker::FindGlowObjectManager();
    Hooker::FindEntityList();

    Logger::Info("Init finished!");
}

int main() {
    Init();

    /*
     *
     * module enable [module]
     * module disable [module]
     *
     */

    printf("\n");
    char input[128];
    for (;;) {
        Logger::CLI();
        cin.getline(input, sizeof(input));
        ProcessCommand(input);
    }
}