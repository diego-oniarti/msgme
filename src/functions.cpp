#include "functions.h"
#include "bot.h"
#include <filesystem>
#include <iostream>
#include <string>

void interactive() {
    Bot bot = get_bot();
    while (true) {
        std::string usrstr;
        std::cin >> usrstr;

        if (usrstr.length()==0) continue;

        switch (usrstr[0]) {
            case 'q':
                exit(0);
            case '-':
                usrstr.erase(0,1);
                bot.sendMsg(usrstr.c_str());
                break;
        }
    }
}

void ask_creds() {
    std::string token, chat;
    std::cout << "Bot token: ";
    std::cin >> token;
    std::cout << "User id: ";
    std::cin >> chat;

    std::filesystem::path home = std::getenv("HOME");
    std::filesystem::path confdir = home / ".config" / "msgme";
    std::filesystem::path confpath = confdir / "creds";

    bool created = std::filesystem::create_directories(confdir);

    FILE *conf = fopen(confpath.c_str(), "w");
    fprintf(conf, "%s\n%s\n", token.c_str(), chat.c_str());
    fclose(conf);
}
