#include "commands.h"
#include "bot.h"

#include <iostream>

int send(int argc, char** argv) {
    if (argc!=1) {
        std::cerr << "Usage:\nmsgme send [message]\n";
        return 1;
    }
    get_bot()->sendMsg(argv[0]);
    return 0;
}
