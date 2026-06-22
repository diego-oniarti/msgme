#include "bot.h"
#include "commands.h"

#include <iostream>

int interactive() {
    Bot *bot = get_bot();
    while (true) {
        std::string usrstr;
        std::getline(std::cin, usrstr);

        if (usrstr.length() == 0) continue;

        switch (usrstr[0]) {
        case 'q': return 0;
        case '-':
            usrstr.erase(0, 1);
            bot->sendMsg(usrstr.c_str());
            break;
        }
    }
}
