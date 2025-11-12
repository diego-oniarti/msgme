#include "bot.h"
#include <filesystem>
#include <iostream>

std::filesystem::path home = std::getenv("HOME");
std::filesystem::path confdir = home / ".config" / "msgme";
std::filesystem::path credspath = confdir / "creds";

Bot::Bot(std::string token, std::string chat): tgbot(token), chat(chat){}

void Bot::sendMsg(const char* msg) {
    tgbot.getApi().sendMessage(chat, msg);
}

Bot get_bot() {
    if (!std::filesystem::exists(credspath)) {
        std::cerr << "Missing credentials.\nSet them with msgme creds" << std::endl;
        exit(1);
    }

    std::string token, chatid;
    std::ifstream config(credspath);
    config >> token >> chatid;

    return Bot(token.c_str(), chatid.c_str());
}
