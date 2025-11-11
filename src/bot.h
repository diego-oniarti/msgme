#pragma once
#include <tgbot/Bot.h>

class Bot {
private:
    TgBot::Bot bot;
    const std::string chat;
public:
    Bot(std::string token, std::string chat);
    void sendMsg(const char* msg);
};

Bot get_bot();
