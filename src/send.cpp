#include "commands.h"
#include "bot.h"

int send(std::string msg) {
    get_bot()->sendMsg(msg.c_str());
    return 0;
}
