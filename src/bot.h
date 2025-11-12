#pragma once
#include <filesystem>
#include <tgbot/Bot.h>

extern std::filesystem::path home, confdir, credspath;

class Bot {
private:
    const std::string chat;
public:
    TgBot::Bot tgbot;
    Bot(std::string token, std::string chat);
    void sendMsg(const char* msg);
};

Bot get_bot();
