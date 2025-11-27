#pragma once
#include <filesystem>
#include <tgbot/Bot.h>

extern std::filesystem::path home, confdir, credspath;

class Bot {
private:
    const std::string chat;
    TgBot::Bot tgbot;
public:
    Bot(std::string token, std::string chat);
    void sendMsg(const char* msg);
    TgBot::Bot* getTgBot();
};

Bot get_bot();
