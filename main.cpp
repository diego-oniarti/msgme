#include <cstdio>
#include <cstring>
#include <iostream>

#include "src/functions.h"
#include "src/bot.h"

void printusage();

int main (int argc, char *argv[]) {
    if (argc > 3) {
        std::cerr << "Too many arguments\n";
        return 1;
    }

    if (argc == 1) {
        printusage();
        return 1;
    }

    if (strcmp(argv[1], "interactive")==0) {
        interactive();
        return 0;
    }

    if (strcmp(argv[1], "send")==0) {
        if (argc!=3) {
            std::cerr << "Usage:\nmsgme send [message]\n";
            exit(1);
        }
        get_bot().sendMsg(argv[2]);
        return 0;
    }

    if (strcmp(argv[1], "config")==0) {
        config();
        return 0;
    }

    if (strcmp(argv[1], "setuser")==0) {
        setuser();
        return 0;
    }

    printusage();
    return 1;
}

void printusage() {
    fprintf(stderr, "Usage: msgme <command> [msg]\nCommands:\ninteractive\nsend\nconfig\nsetuser\n");
}
