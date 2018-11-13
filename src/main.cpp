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
    noflash,
    aimbot
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
            Logger::Error("Kisak says cheating is bad, no help for you.");
            break;
        case module:
            // check for module name and perform operation on it
            if (parts.size() < 2) {
                Logger::Error("You need to State a module!");
                return;
            }

            if (parts[1] == "list")
                mod = list;
            else if (parts[1] == "glow")
                mod = glow;
            else if (parts[1] == "aimbot")
                mod = aimbot;
            else if (parts[1] == "bhop")
                mod = bhop;
            else if (parts[1] == "triggerbot")
                mod = triggerbot;
            else if (parts[1] == "noflash")
                mod = noflash;
            else if (parts[1] == "all")
                mod = all;

            if (mod != list) {
                operation = enable;
            }

            switch (mod) {
                case all:
                    if (operation == enable) {
                        Misc::BHop::Enable();
                        Aimbot::Enable();
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
                case aimbot:
                    Aimbot::Enable();
                    break;
                default:
                    Logger::Error("Unknown Module!");
            }
            break;
        default:
            Logger::Error("Unknown Command, try `help`");
    }
}

void Init() {
    mouse.Init(ms);
    keyboard.Init(kb);
    Sigger::Init();
    Sigger::FindLocalPlayer();
    Sigger::FindForceJumpAddress();
    Sigger::FindGlowObjectManager();
    Sigger::FindEntityList();
    Sigger::FindGlobalVars();
    Sigger::FindEngineFunctions();

    Logger::Info("Init finished!");
    std::thread Run(Run::Run);
    Run.detach();
}

int main() {
    Init();
    printf("\n");
    char input[128];
    for (;;) {
        Logger::CLI();
        cin.getline(input, sizeof(input));
        ProcessCommand(input);
    }
}