#include "bot.h"
#include <filesystem>
#include <iostream>

Bot::Bot(std::string token, std::string chat): bot(token), chat(chat){}

void Bot::sendMsg(const char* msg) {
    bot.getApi().sendMessage(chat, msg);
}

Bot get_bot() {
    std::filesystem::path home = std::getenv("HOME");
    std::filesystem::path credsfile = home / ".config" / "msgme" / "creds";

    if (!std::filesystem::exists(credsfile)) {
        std::cerr << "Missing credentials.\nSet them with msgme creds" << std::endl;
        exit(1);
    }

    std::string token, chatid;
    std::ifstream config(credsfile);
    config >> token >> chatid;

    return Bot(token.c_str(), chatid.c_str());
}
