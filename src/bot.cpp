#include "bot.h"
#include <filesystem>
#include <iostream>

static Bot *bot_instance = NULL;

std::filesystem::path home = std::getenv("HOME");
std::filesystem::path confdir = home / ".config" / "msgme";
std::filesystem::path credspath = confdir / "creds";

Bot::Bot(std::string token, std::string chat): tgbot(token), chat(chat){}

void Bot::sendMsg(const char* msg) {
    tgbot.getApi().sendMessage(chat, msg);
}

TgBot::Bot* Bot::getTgBot() {
    return &(this->tgbot);
}

Bot *get_bot() {
    if (bot_instance!=NULL) return bot_instance;
    if (!std::filesystem::exists(credspath)) {
        std::cerr << "Missing credentials.\nSet them with msgme config" << std::endl;
        exit(1);
    }

    std::string token, chatid;
    std::ifstream config(credspath);
    config >> token >> chatid;

    bot_instance = new Bot(token.c_str(), chatid.c_str());
    return bot_instance;
}
