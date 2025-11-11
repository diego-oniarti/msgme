#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <tgbot/tgbot.h>

int main (int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Too many arguments\n";
        return 1;
    }

    std::filesystem::path home = std::getenv("HOME");
    std::filesystem::path credsfile = home / ".config" / "msgme" / "creds";

    if (!std::filesystem::exists(credsfile)) {
        std::cerr << "Missing credentials.\nSet them with msgmecreds" << std::endl;
        return 1;
    }

    std::string token, chatid;
    std::ifstream config(credsfile);
    config >> token >> chatid;

    TgBot::Bot bot(token);

    if (argc == 2) {
        bot.getApi().sendMessage(chatid, argv[1]);
        return 0;
    }

    while (true) {
        std::string usrstr;
        std::cin >> usrstr;

        if (usrstr.length()==0) continue;

        switch (usrstr[0]) {
            case 'q':
                return 0;
            case '-':
                usrstr.erase(0,1);
                bot.getApi().sendMessage(chatid, usrstr);
                break;
        }
    }

    return 0;
}
