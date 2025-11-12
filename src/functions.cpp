#include "functions.h"
#include "bot.h"
#include <algorithm>
#include <atomic>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
#include <tgbot/tgbot.h>
#include <thread>

void interactive() { Bot bot = get_bot();
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

void config() {
    std::string token, chat;
    std::cout << "Bot token: ";
    std::getline(std::cin, token);
    std::cout << "User id: (leave empty if unknown)";
    std::getline(std::cin, chat);

    bool created = std::filesystem::create_directories(confdir);

    FILE *conf = fopen(credspath.c_str(), "w");
    fprintf(conf, "%s\n%s\n", token.c_str(), chat.c_str());
    fclose(conf);

    if (chat.empty()) {
        std::cout << "No userid given. Launch assistant? [Y, n]" << std::endl;
        std::string reply;
        getline(std::cin, reply);
        std::transform(reply.begin(), reply.end(), reply.begin(), ::tolower);
        if (reply=="no" || reply=="n") return;
        setuser();
    }
}

void setuser() {
    Bot bot = get_bot();
    TgBot::Bot *tgbot = &bot.tgbot;

    long id = 0;
    tgbot->getEvents().onAnyMessage([&id](TgBot::Message::Ptr message) {
        printf("[%ld - %s %s]: %s\n",
                message->chat->id,
                message->chat->firstName.c_str(),
                message->chat->lastName.c_str(),
                message->text.c_str()
                );
        fflush(stdout);
        id = message->chat->id;
    });

    std::atomic<bool> run(true);
    std::thread waiter([&run](){
            std::string dummy;
            std::getline(std::cin, dummy);
            run=false;
            });

    TgBot::TgLongPoll longpoll(*tgbot, 100, 1);
    std::cout << "Send a message to the bot. Press enter to stop" << std::endl;
    while (run) {
        longpoll.start();
    }
    waiter.join();

    printf("ID: %ld\nSave to config file? [Y, n]\n", id);
    std::string reply;
    getline(std::cin, reply);
    std::transform(reply.begin(), reply.end(), reply.begin(), ::tolower);

    if (reply=="no" || reply=="n") return;

    FILE *creds = fopen(credspath.c_str(), "r+");
    char c;
    do {
        c = fgetc(creds);
    }while(c!='\n' && c!=EOF);
    fprintf(creds, "%ld\n", id);
    fclose(creds);
}
