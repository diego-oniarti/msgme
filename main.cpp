#include <cstdio>
#include <cstring>
#include <iostream>
#include <tgbot/tgbot.h>

#include "src/functions.h"
#include "src/bot.h"

int main (int argc, char *argv[]) {
    if (argc > 3) {
        std::cerr << "Too many arguments\n";
        return 1;
    }

    if (argc==1) {
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

    if (strcmp(argv[1], "creds")==0) {
        ask_creds();
        return 0;
    }

    if (strcmp(argv[1], "getuser")==0) {
        std::cerr << "Not implemented\n";
        return 1;
    }

    return 0;
}
