#include "commands.h"
#include "bot.h"

#include <tgbot/tgbot.h>

int setuser(int argc, char** argv) {
    Bot bot = get_bot();
    TgBot::Bot *tgbot = bot.getTgBot();

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

    if (reply=="no" || reply=="n") return 0;

    FILE *creds = fopen(credspath.c_str(), "r+");
    char c;
    do {
        c = fgetc(creds);
    }while(c!='\n' && c!=EOF);
    fprintf(creds, "%ld\n", id);
    fclose(creds);

    return 0;
}
