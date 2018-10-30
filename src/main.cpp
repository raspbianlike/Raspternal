#include "Zero.hpp"

#include "Hacks/hacks.hpp"
#include "Hacks/Run.hpp"

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
    // this does not work yet
    vector<string> parts;
    parts = split(message, ' ');

    cmds cmd;
    modules mod;
    operations operation = enable;
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
            if (parts.size() < 1) {
                Logger::Error("Unknown command!");
                return;
            }

            if (parts[1] == "list")
                mod = list;
            else if (parts[1] == "glow")
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
                        Misc::BHop::Enable();
                        Glow::Enable();
                        Triggerbot::Enable();
                        Misc::NoFlash::Enable();
                    } else if (operation == disable) {
                        Misc::BHop::Enable();
                        Glow::Enable();
                        Triggerbot::Enable();
                        Misc::NoFlash::Enable();
                    }
                    break;
                case list:
                    Logger::Modules();
                    break;
                case bhop:
                    Misc::BHop::Enable();
                    break;
                case glow:
                    Glow::Enable();
                    break;
                case triggerbot:
                    Triggerbot::Enable();
                    break;
                case noflash:
                    Misc::NoFlash::Enable();
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
    keyboard.Init();
    Sigger::Init();
    Sigger::FindLocalPlayer();
    Sigger::FindForceJumpAddress();
    Sigger::FindGlowObjectManager();
    Sigger::FindEntityList();
    Sigger::FindGlobalVars();

    Logger::Info("Init finished!");
    std::thread Run(Run::Run);
    Run.detach();
}

int main() {
    //*(int*) 0x0 = 0;
    Init();
    printf("\n");
    char input[128];
    for (;;) {
        Logger::CLI();
        cin.getline(input, sizeof(input));
        ProcessCommand(input);
    }
}