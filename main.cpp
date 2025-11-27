#include <map>
#include <cstdio>
#include <cstring>
#include <string>

#include "src/commands.h"

void printusage();

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printusage();
        return 1;
    }

    // Print help
    if (strcmp(argv[1], "-h")==0) {
        printusage();
        return 0;
    }

    std::map<std::string, int(*)(int, char**)> comandi = {
        { "interactive", interactive },
        { "send", send },
        { "config", config },
        { "setuser", setuser },
    };

    auto cmd = comandi.find(argv[1]);
    if (cmd == comandi.end()) {
        printusage();
        return 1;
    }

    return (*cmd).second(argc-2, argv+2);
}

void printusage() {
    fprintf(stderr, "Usage: msgme <command> [msg]\nCommands:\ninteractive\nsend\nconfig\nsetuser\n");
}
